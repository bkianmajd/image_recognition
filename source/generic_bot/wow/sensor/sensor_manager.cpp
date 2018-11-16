#include "generic_bot/wow/sensor/sensor_manager.h"

#include <iostream>

namespace bot {
namespace wow {
namespace {

const std::string kBigImageName = "screenshot.jpg";

}  // namespace

SensorManager::SensorManager(
    const helpers::DirectoryFinder& templated_image_directory)
    : templated_image_directory_(templated_image_directory),
      template_recognition_manager_(templated_image_directory_,
                                    &simple_recognition_) {}

bool SensorManager::Initialize() {
  // Template recognition manager is injected into the detectors
  detectors_ = wow_object_detector_factory_.GetDetectors(
      &template_recognition_manager_, templated_image_directory_);

  for (IDetector<DetectedObject>* detector : detectors_) {
    if (!detector->RegisterTemplateImages(templated_image_directory_)) {
      std::cerr << "failed to register template" << std::endl;
    }
  }

  return true;
}

void SensorManager::UpdateBigImage(
    const std::vector<char>& big_image_raw_data) {
  if (!template_recognition_manager_.RemoveImage(kBigImageName)) {
    // NO-OPT - mainly because the first RemoveImage will fail
  }

  // Store the big image
  if (!template_recognition_manager_.StoreImage(kBigImageName,
                                                big_image_raw_data)) {
    std::cerr << "Failed to store image" << std::endl;
  }
}

const std::vector<DetectedObject>& SensorManager::DetectObjects() {
  detected_objects_.clear();
  // Cycle through the player spell detectors
  for (IDetector<DetectedObject>* detector : detectors_) {
    detector->Update(kBigImageName, &detected_objects_);
  }
  return detected_objects_;
}

}  // wow
}  // bot
