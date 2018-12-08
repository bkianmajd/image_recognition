#include "wow_detectors/generic_detector.h"

#include <iostream>

#include "helpers/file_manager/file_manager.h"

namespace bot {
namespace wow {

GenericDetector::GenericDetector(
    const std::string& template_image_name,
    const DetectedObject& detected_object_prototype,
    template_recognition::TemplateRecognitionManager*
        template_recognition_manager)
    : template_image_name_(template_image_name),
      template_recognition_manager_(template_recognition_manager),
      detected_object_prototype_(detected_object_prototype) {}

bool GenericDetector::RegisterTemplateImages(
    const helpers::DirectoryFinder& directory_finder) {
  std::string abs_path_image =
      directory_finder.GetAbsPathOfTargetFile(template_image_name_);

  // Grab the raw data
  std::vector<char> raw_data = helpers::FileManager::ReadFile(abs_path_image);

  if (raw_data.size() == 0) {
    std::cerr << "Raw data size = 0 " << abs_path_image << std::endl;
    return false;
  }

  // Store the image
  if (!template_recognition_manager_->StoreImage(template_image_name_,
                                                 raw_data)) {
    std::cerr << "Failed to store image " << abs_path_image << std::endl;
    return false;
  }

  return true;
}

void GenericDetector::Update(const std::string& big_image_name,
                             std::vector<DetectedObject>* detected_types) {
  template_recognition::Point point;
  if (!template_recognition_manager_->TemplateMatch(
          big_image_name, template_image_name_, &point)) {
    std::cerr << "Generic detector: Failed to reg point" << template_image_name_
              << std::endl;
    return;
  }

  if (!point.isValid) {
    return;
  }

  detected_object_prototype_.point.x_location = point.x;
  detected_object_prototype_.point.y_location = point.y;
  detected_types->push_back(detected_object_prototype_);
}

}  // namespace bot
}  // namespace wow
