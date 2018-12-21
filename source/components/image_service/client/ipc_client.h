#ifndef IPC_CLIENT_H_
#define IPC_CLIENT_H_

#include "libraries/postal_service/postal_service.h"
#include "libraries/postal_service/utility/mail_distributor_queue.h"
#include "libraries/postal_service/utility/post_card_queue.h"
#include "schema/compiled_files/image_request_response_commands.pb.h"

namespace ipc {
class IpcClient {
 public:
  // Must be instantiated from qt main
  IpcClient();

  void AsyncInit(const com_layer::ConnectionInfo& connection_info);

  bool IsInit();

  // Send the binary - blocking clal
  bool SendImage(const std::vector<char>& binary,
                 const std::string& image_name);

 private:
  postal_service::PostalService client_;
  postal_service::MailDistributorQueue response_queue_;
};

}  // namespace ipc

#endif  // IPC_CLIENT_H_
