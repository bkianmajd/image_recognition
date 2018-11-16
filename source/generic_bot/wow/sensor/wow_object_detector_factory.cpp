#ifndef WOW_OBJECT_DETECTOR_FACTORY_
#define WOW_OBJECT_DETECTOR_FACTORY_

#include <vector>

#include "generic_bot/idetector.h"
#include "generic_bot/wow/sensor/sensor_def.h"
#include "template_recognition/template_recognition_manager.h"

namespace bot {
namespace wow {

// Generic detector should take in a string
// and the enum and add to the vector...this is
// a lot easier than creating a series of implemented classes

class WowObjectDetectorFactory {
 public:
  WowObjectDetectorFactory() {}

  std::vector<IDetector<DetectedObject>*> GetDetectors(
      template_recognition::TemplateRecognitionManager*
          template_recognition_manager,
      const helpers::DirectoryFinder& templated_image_directory) {

  }
};

}  // namespace wow
}  // namespace bot

#endif // WOW_OBJECT_DETECTOR_FACTORY_
