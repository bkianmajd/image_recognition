#ifndef WOW_OBJECT_DETECTOR_FACTORY_
#define WOW_OBJECT_DETECTOR_FACTORY_

#include <unordered_map>
#include <vector>

#include "generic_bot/idetector.h"
#include "generic_bot/wow/sensor/sensor_def.h"
#include "template_recognition/template_recognition_manager.h"

namespace bot {
namespace wow {
using ObjectMap = std::unordered_map<std::string, DetectedObject>;
namespace {

void AddPlayerSpells(ObjectMap* object_map) {
  DetectedObject prototype;
  prototype.image_type = ImageType::IMAGE_TYPE_PLAYER_SPELL;

  // fireball
  prototype.player_spell = PlayerSpell::PLAYER_SPELL_FIREBALL;
  object_map->at("fireball.jpg") = prototype;
}

}  // namespace

class WowObjectDetectorFactory {
 public:
  WowObjectDetectorFactory() { AddPlayerSpells(&detected_object_map_); }

  std::vector<IDetector<DetectedObject>*> GetDetectors(
      template_recognition::TemplateRecognitionManager*
          template_recognition_manager,
      const helpers::DirectoryFinder& templated_image_directory) {

  }

 private:
  ObjectMap detected_object_map_;
};

}  // namespace wow
}  // namespace bot

#endif  // WOW_OBJECT_DETECTOR_FACTORY_
