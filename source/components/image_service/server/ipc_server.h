#ifndef IPC_SERVER_H_
#define IPC_SERVER_H_

#include "libraries/postal_service/postal_service.h"
#include "libraries/postal_service/utility/mail_distributor_queue.h"
#include "schema/compiled_files/image_request_response_commands.pb.h"

namespace ipc {
class IpcServer {
 public:
  // Must be instantiated from qt main
  IpcServer();

  void AsyncInit(const com_layer::ConnectionInfo& connection_info);

  bool IsInit();

  // Returns true if server protocol was succesfully established, returns false
  // if there is a critical error
  bool CheckForImage(std::vector<char>* bytes);

 private:
  void SendAcknowledgement();

  postal_service::PostalService server_;
  postal_service::MailDistributorQueue request_queue_;
};

}  // namespace ipc

#endif  // IPC_SERVER_H_
