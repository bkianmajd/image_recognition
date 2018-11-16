#ifndef SENSOR_MANAGER_H_
#define SENSOR_MANAGER_H_

#include <string>
#include <vector>

#include "generic_bot/idetector.h"
#include "generic_bot/wow/sensor/sensor_def.h"
#include "generic_bot/wow/sensor/wow_object_detector_factory.h"
#include "helpers/directory_finder.h"
#include "template_recognition/simple/simple_recognition.h"
#include "template_recognition/template_recognition_manager.h"

namespace bot {
namespace wow {

/// SensorManager aggregates the detectors
class SensorManager {
 public:
  SensorManager(const helpers::DirectoryFinder& templated_image_directory);

  bool Initialize();

  void UpdateBigImage(const std::vector<char>& big_image_raw_data);

  const std::vector<DetectedObject>& DetectObjects();

 private:
  const helpers::DirectoryFinder templated_image_directory_;
  template_recognition::SimpleRecognition simple_recognition_;
  template_recognition::TemplateRecognitionManager
      template_recognition_manager_;

  WowObjectDetectorFactory wow_object_detector_factory_;

  // DetectedPlayerSpell
  std::vector<DetectedObject> detected_objects_;
  std::vector<IDetector<DetectedObject>*> detectors_;
};

}  // namespace wow
}  // namespace bot

#endif  // SENSOR_MANAGER_H_
