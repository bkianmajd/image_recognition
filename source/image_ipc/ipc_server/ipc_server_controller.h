#ifndef IPC_SERVER_CONTROLLER_H_
#define IPC_SERVER_CONTROLLER_H_

#include <chrono>
#include <thread>
#include "helpers/file_manager/file_manager.h"
#include "postal_service/imail_distributor.h"
#include "postal_service/postal_service.h"
#include "postal_service/utility/post_card_queue.h"

#include "postal_service/utility/post_card_queue.h"

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
                      postal_service::PostCardQueue* response_handler);

  // Initialize the communication with the first client and ensure connection
  // This function must be called from the main thread due to exec()
  void Initialize();
  void Run();

 private:
  // Health status, context of state is changed inside here.
  void UpdateState();

  State state_;
  postal_service::PostalService* postal_service_;
  postal_service::IMailDistributor* imail_distributor_;
  postal_service::PostCardQueue* response_handler_;
};

}  // namespace ipc
}  // namespace ipc_server

#endif  // IPC_SERVER_CONTROLLER_H_
