#include "image_ipc/ipc_server/ipc_server_controller.h"

namespace ipc {
namespace ipc_server {
namespace {

constexpr std::chrono::seconds kInitTimeout = std::chrono::seconds(5);

}  // namespace

IpcServerController::IpcServerController(
    postal_service::PostalService* postal_service,
    postal_service::IMailDistributor* imail_distributor,
    ResponseHandler* response_handler)
    : postal_service_(postal_service),
      imail_distributor_(imail_distributor),
      response_handler_(response_handler) {}

bool IpcServerController::Initialize() {
  if (postal_service_ == nullptr || imail_distributor_ == nullptr ||
      response_handler_ == nullptr) {
    return false;
  }

  postal_service_->Init();
  int max_counter = kInitTimeout / std::chrono::milliseconds(50);
  int counter = 0;

  while (!postal_service_->IsOpen()) {
    if (counter++ > max_counter) {
      return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  return true;
}

void IpcServerController::Run() {
  std::cout << "Starting run operation\n";
  do {
    UpdateState();

    // Receieve something
    postal_service_->GetMail(*imail_distributor_);

    // Send response
    if (!response_handler_->Empty()) {
      postal_service_->SendPostCard(*response_handler_);
    }
  } while (state_ == State::STATE_RUNNING);

  std::cout << "Ending run operation\n";
}

void IpcServerController::UpdateState() {
  if (postal_service_->IsOpen()) {
    state_ = STATE_IDLE;
  }
}

}  // namespace ipc
}  // namespace ipc_server
