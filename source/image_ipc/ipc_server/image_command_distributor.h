#ifndef IMAGE_COMMAND_DISTRIBUTOR_H_
#define IMAGE_COMMAND_DISTRIBUTOR_H_

#include "image_ipc/file_manager/file_manager.h"
#include "image_ipc/ipc_server/response_handler.h"
#include "postal_service/imail_distributor.h"
#include "schema/compiled_files/template_match.pb.h"

namespace ipc {
namespace ipc_server {

class ImageCommandDistributor : public postal_service::IMailDistributor {
 public:
  ImageCommandDistributor(FileManager* file_manager,
                          ResponseHandler* response_handler);

  /// Postal service calls this to distribute a byte array
  /// this function therefore should decode the byte array and pass it up.
  /// This function decodes the string into ImageCommands and passes it up to
  /// respective managers.
  /// TODO() This argument should be an any
  void Distribute(const google::protobuf::Any& any) override;

 private:
  void Handle(const ipc_interface::StoreImageRequest& request,
              ipc_interface::StoreImageResponse* response);

  FileManager* file_manager_;
  ResponseHandler* response_handler_;
};

}  // namespace ipc
}  // namespace ipc_server

#endif  // IMAGE_COMMAND_DISTRIBUTOR_H_
