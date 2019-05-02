#ifndef IMAGE_COMMAND_DISPATCHER_H_
#define IMAGE_COMMAND_DISPATCHER_H_

#include <string>
#include <unordered_map>
#include "gtest/gtest_prod.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager.h"
#include "schema/compiled_files/image_request_response_commands.pb.h"
#include "template_recognition/template_recognition_interface.h"

namespace ipc {
namespace ipc_server {

/// Class handles the protocol buffers directly from the ImageRequestResponse
/// protofile interface. Converts protobuf to api functions that talk directly
/// to the open cv interface
class ImageCommandDispatcher {
 public:
  ImageCommandDispatcher(
      helpers::DirectoryFinder* session_directory, FileManager* file_manager,
      template_recognition::TemplateRecognitionInterface* template_recognition);

  void Handle(const ipc_interface::StoreImageRequest& request,
              ipc_interface::StoreImageResponse* response);

  void Handle(const ipc_interface::TemplateMatchRequest& request,
              ipc_interface::TemplateMatchResponse* response);

 private:
  FRIEND_TEST(ImageCommandDispatcherTest, GetTemplateIdTest);
  // The data directory is where all the images are currently stored
  helpers::DirectoryFinder* data_directory_;

  // The file manager wraps certain function calls. All inputs are abs path.
  FileManager* file_manager_;

  // TemplateRecognitionInterface
  template_recognition::TemplateRecognitionInterface* template_recognition_;

  int GetTemplateIdOrRegisterTemplate(const std::string& image_name);

  // The map key is the filename, the map value is the stored templateId
  std::unordered_map<std::string, template_recognition::TemplateId>
      stored_template_id_;
};

}  // namespace ipc
}  // namespace ipc_server

#endif  // IMAGE_COMMAND_DISPATCHER_H_
