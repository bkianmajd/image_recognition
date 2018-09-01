#include "image_ipc/ipc_server/ipc_server_controller.h"

#include <chrono>
#include <thread>

namespace ipc {
namespace ipc_server {
namespace {

const std::chrono::milliseconds kRunDuration = std::chrono::milliseconds(500);

}  // namespace

IpcServerController::IpcServerController(
    postal_service::PostalService* postal_service,
    postal_service::IMailDistributor* imail_distributor,
    postal_service::PostCardQueue* response_handler)
    : postal_service_(postal_service),
      imail_distributor_(imail_distributor),
      response_handler_(response_handler) {}

void IpcServerController::Initialize() {
  if (postal_service_ == nullptr || imail_distributor_ == nullptr ||
      response_handler_ == nullptr) {
    return;
  }

  com_layer::ConnectionInfo connection_info;
  std::cout << "Server: Listening for the first connection on port number "
            << connection_info.port << std::endl;

  // TODO(): return the connected socket address
  // TODO(): Add a close function to stop listening
  postal_service_->AsyncInit(connection_info);
}

void IpcServerController::Run() {
  if (postal_service_->WaitForOpen()) {
    std::cout << "Initialization success" << std::endl;
    state_ = State::STATE_RUNNING;
  }

  std::cout << "Starting run operation\n";
  do {
    std::this_thread::sleep_for(kRunDuration);

    // UpdateState();

    // Receieve something
    postal_service_->GetMail(*imail_distributor_);

    // Send response(s)
    while (!response_handler_->Empty()) {
      postal_service_->SendPostCard(*response_handler_);
    }
  } while (state_ == State::STATE_RUNNING);

  std::cout << "Ending run operation\n";
}

void IpcServerController::UpdateState() {
  if (!postal_service_->IsOpen()) {
    std::cout << "IpcServerController: Postal service is not open, transfering "
                 "state to idle"
              << std::endl;
    state_ = STATE_IDLE;
  }
}

}  // namespace ipc
}  // namespace ipc_server
