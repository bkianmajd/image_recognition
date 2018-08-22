#ifndef IPC_SERVER_CONTROLLER_H_
#define IPC_SERVER_CONTROLLER_H_

#include <chrono>
#include <thread>
#include "image_ipc/file_manager/file_manager.h"
#include "image_ipc/ipc_server/response_handler.h"
#include "postal_service/imail_distributor.h"
#include "postal_service/postal_service.h"

namespace ipc {
namespace ipc_server {

enum State {
  STATE_CONSTRUCTING = 0,
  STATE_IDLE,
  STATE_RUNNING,
};

class IpcServerController {
 public:
  IpcServerController(postal_service::PostalService* postal_service,
                      postal_service::IMailDistributor* imail_distributor,
                      ResponseHandler* response_handler);

  // Initialize the communication with the first client and ensure connection
  bool Initialize();
  void Run();

 private:
  // Health status, context of state is changed inside here.
  void UpdateState();

  State state_;
  postal_service::PostalService* postal_service_;
  postal_service::IMailDistributor* imail_distributor_;
  ResponseHandler* response_handler_;
};

}  // namespace ipc
}  // namespace ipc_server

#endif  // IPC_SERVER_CONTROLLER_H_
