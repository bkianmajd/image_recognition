#ifndef SENSOR_MANAGER_H_
#define SENSOR_MANAGER_H_

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "generic_bot/wow/sensor/sensor_def.h"
#include "helpers/directory_finder.h"
#include "template_recognition/template_recognition_manager.h"

namespace bot {
namespace wow {
namespace {

const std::string kBigImageName = "screenshot.jpg";

}  // namespace

class SensorManager {
 public:
  SensorManager(const helpers::DirectoryFinder& templated_image_directory);

  bool Initialize() {
    if (!WowImageRegistry.Initialize()) {
      std::cerr << "WOW Image Registry failed to initialize";
      return false;
    }

    // Register all the template images - with the template_recognition manager
    const std::vector<std::string>& template_names =
        image_registrar_.GetTemplateNames();

    for (const std::string& template_image_name : template_names) {
      // Grab the raw data
      std::vector<char> raw_data = file_manager_.ReadFile(template_image_name);
      if (raw_data.size() == 0) {
        std::cerr << "Raw data size = 0 " << template_image_name << std::endl;
        return false;
      }

      // Store the image
      if (!template_recognition_manager_->StoreImage(template_image_name,
                                                     raw_data)) {
        std::cerr << "Failed to store image " << template_image_name
                  << std::endl;
        return false;
      }
    }

    return true;
  }

  std::vector<DetectedObject> GetDetectedObjects(
      const std::vector<char>& big_image_raw_data) {
    // Instantiate the return vector
    std::vector<DetectedObject> detected_objects;

    // Store the big image
    if (!template_recognition_manager_->StoreImage(kBigImageName,
                                                   big_image_raw_data)) {
      std::cerr << "Failed to store image" << std::endl;
      return detected_objects;
    }

    // Cycle through the template names
    const std::vector<std::string>& template_names =
        image_registrar_.GetTemplateNames();

    for (const std::string& template_name : template_names) {
      ObjectDetector* object_detector =
          image_registrar_.GetCorrespondObjectDetector(template_name);

      // An ObjectDetector

      template_recognition_manager_->TemplateMatch(kBigImageName,
                                                   template_name, );
    }

    if (!template_recognition_manager_->RemoveImage(kBigImageName)) {
      std::cerr << "Failed to remove image" << std::endl;
      detected_objects;
    }

    return detected_objects;
  }

 private:
  const helpers::DirectoryFinder templated_image_directory_;
  helpers::FileManager file_manager_;

  // Image registry stores all the wow image templates
  WowImageRegistry image_registrar_;

  template_recognition::TemplateRecognitionManager*
      template_recognition_manager_;
};

}  // namespace wow
}  // namespace bot

#endif  // SENSOR_MANAGER_H_
