#ifndef IMAGE_COMMAND_CREATOR_H_
#define IMAGE_COMMAND_CREATOR_H_

#include "image_ipc/ipc_server/image_command_dispatcher.h"
#include "postal_service/imail_distributor.h"
#include "postal_service/utility/post_card_queue.h"
#include "schema/compiled_files/image_request_response.pb.h"

namespace ipc {
namespace ipc_server {

/// Converts an any protofile to an image command and distributes the
/// command to the dispatcher
class ImageCommandCreator : public postal_service::IMailDistributor {
 public:
  ImageCommandCreator(ImageCommandDispatcher* dispatcher,
                      postal_service::PostCardQueue* response_handler);

  /// Postal service calls this to distribute a byte array
  /// this function therefore should decode the byte array and pass it up.
  /// This function decodes the string into ImageCommands and passes it up to
  /// respective managers.
  /// TODO() This argument should be an any
  void Distribute(const google::protobuf::Any& any) override;

 private:
  ImageCommandDispatcher* dispatcher_;
  postal_service::PostCardQueue* response_handler_;
};

}  // namespace ipc
}  // namespace ipc_server

#endif  // IMAGE_COMMAND_CREATOR_H_
