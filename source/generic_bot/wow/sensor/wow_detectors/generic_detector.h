#ifndef GENERIC_DETECTOR_H_
#define GENERIC_DETECTOR_H_

#include "generic_bot/idetector.h"
#include "generic_bot/wow/sensor/sensor_def.h"
#include "helpers/directory_finder.h"
#include "template_recognition/template_recognition_manager.h"

namespace bot {
namespace wow {

class GenericDetector : public IDetector<DetectedObject> {
 public:
  GenericDetector(const std::string& template_image_name,
                  const DetectedObject& detected_object_prototype,
                  template_recognition::TemplateRecognitionManager*
                      template_recognition_manager);

  bool RegisterTemplateImages(
      const helpers::DirectoryFinder& directory_finder) override;

  // Updates a vector of a Detector type struct (i.e. list of detected objects)
  void Update(const std::string& big_image_name,
              std::vector<DetectedObject>* detected_types) override;

 private:
  const std::string& template_image_name_;

  template_recognition::TemplateRecognitionManager*
      template_recognition_manager_;

  DetectedObject detected_object_prototype_;
};

}  // namespace wow
}  // namespace bot

#endif  // GENERIC_DETECTOR_H_
