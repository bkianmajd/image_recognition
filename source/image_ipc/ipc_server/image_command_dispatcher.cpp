#include "image_ipc/ipc_server/image_command_dispatcher.h"

namespace ipc {
namespace ipc_server {

ImageCommandDispatcher::ImageCommandDispatcher(
    helpers::DirectoryFinder* session_directory, FileManager* file_manager,
    template_recognition::TemplateRecognitionInterface* template_recognition)
    : data_directory_(session_directory),
      file_manager_(file_manager),
      template_recognition_(template_recognition) {}

void ImageCommandDispatcher::Handle(
    const ipc_interface::StoreImageRequest& request,
    ipc_interface::StoreImageResponse* response) {
  std::string abs_file =
      data_directory_->GetAbsPathOfTargetFile(request.image_name());

  bool result = file_manager_->StoreFile(request.image().c_str(),
                                         request.image().size(), abs_file);
  response->set_success(result);
}

}  // namespace ipc
}  // namespace ipc_server
