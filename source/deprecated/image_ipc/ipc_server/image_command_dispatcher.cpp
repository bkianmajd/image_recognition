#include "image_ipc/ipc_server/image_command_dispatcher.h"
#include "template_recognition/template_recognition_defs.h"

namespace ipc {
namespace ipc_server {
namespace {

constexpr int kFailedToRegisterTemplateError = -1;

}  // namespace

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

void ImageCommandDispatcher::Handle(
    const ipc_interface::TemplateMatchRequest& request,
    ipc_interface::TemplateMatchResponse* response) {
  // Store failed response
  response->set_success(false);

  // Send the big image
  if (!template_recognition_->RegisterImage(
          data_directory_->GetAbsPathOfTargetFile(request.big_image_name()))) {
    std::cerr << "ImageCommandDispatcher:Failed to register image "
              << data_directory_->GetAbsPathOfTargetFile(
                     request.big_image_name())
              << std::endl;
    return;
  }

  // Send the small image
  int template_id =
      GetTemplateIdOrRegisterTemplate(request.template_image_name());
  if (template_id == kFailedToRegisterTemplateError) {
    std::cerr << "Failed to register template "
              << data_directory_->GetAbsPathOfTargetFile(
                     request.template_image_name())
              << std::endl;
    return;
  }

  // Get the point
  template_recognition::Point point =
      template_recognition_->GetTemplateMatch(template_id);
  response->set_success(point.isValid);
  response->set_x_location(point.x);
  response->set_y_location(point.y);
}

int ImageCommandDispatcher::GetTemplateIdOrRegisterTemplate(
    const std::string& image_name) {
  auto it = stored_template_id_.find(image_name);
  if (it != stored_template_id_.end()) {
    return it->second;
  }

  int next_template_id = stored_template_id_.size();
  if (!template_recognition_->RegisterTemplate(
          next_template_id,
          data_directory_->GetAbsPathOfTargetFile(image_name))) {
    return kFailedToRegisterTemplateError;
  }

  stored_template_id_[image_name] = next_template_id;
  return next_template_id;
}

}  // namespace ipc
}  // namespace ipc_server
