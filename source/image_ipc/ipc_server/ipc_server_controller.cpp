#include "image_ipc/ipc_server/ipc_server_controller.h"

namespace ipc {
namespace ipc_server {
namespace {}  // namespace

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

  com_layer::ConnectionInfo connection_info;
  std::cout << "Server: Listening for the first connection on port number "
            << connection_info.port << std::endl;

  // TODO(): return the connected socket address
  // TODO(): Add a close function to stop listening
  postal_service_->Init(connection_info);

  if (postal_service_->IsOpen()) {
    std::cout << "Initialization success" << std::endl;
    return true;
  }

  return false;
}

void IpcServerController::Run() {
  std::cout << "Starting run operation\n";
  do {
    UpdateState();

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
  if (postal_service_->IsOpen()) {
    state_ = STATE_IDLE;
  }
}

}  // namespace ipc
}  // namespace ipc_server
