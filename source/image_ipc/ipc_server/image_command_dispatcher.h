#ifndef IMAGE_COMMAND_DISPATCHER_H_
#define IMAGE_COMMAND_DISPATCHER_H_

#include <string>
#include "helpers/directory_finder.h"
#include "image_ipc/file_manager/file_manager.h"
#include "schema/compiled_files/image_request_response.pb.h"
#include "template_recognition/template_recognition_defs.h"
#include "template_recognition/template_recognition_interface.h"

// Change  template_match to image request response interface

namespace ipc {
namespace ipc_server {

/// Class handles the protocol buffers directly from the ImageRequestResponse
/// protofile interface
class ImageCommandDispatcher {
 public:
  ImageCommandDispatcher(
      helpers::DirectoryFinder* session_directory, FileManager* file_manager,
      template_recognition::TemplateRecognitionInterface* template_recognition);

  void Handle(const ipc_interface::StoreImageRequest& request,
              ipc_interface::StoreImageResponse* response);

 private:
  // The data directory is where all the images are currently stored
  helpers::DirectoryFinder* data_directory_;

  // The file manager wraps certain function calls. All inputs are abs path.
  FileManager* file_manager_;

  // TemplateRecognitionInterface
  template_recognition::TemplateRecognitionInterface* template_recognition_;
};

}  // namespace ipc
}  // namespace ipc_server

#endif  // IMAGE_COMMAND_DISPATCHER_H_
