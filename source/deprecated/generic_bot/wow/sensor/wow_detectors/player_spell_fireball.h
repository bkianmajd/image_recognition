#ifndef PLAYER_SPELL_FIREBALL_H_
#define PLAYER_SPELL_FIREBALL_H_

#include "generic_bot/idetector.h"
#include "generic_bot/wow/sensor/sensor_def.h"
#include "helpers/directory_finder.h"
#include "template_recognition/template_recognition_manager.h"

namespace bot {
namespace wow {

class PlayerSpellFireball : public IDetector<DetectedPlayerSpell> {
 public:
  PlayerSpellFireball(
      template_recognition::Manager* template_recognition_manager);

  bool RegisterTemplateImages(
      const helpers::DirectoryFinder& directory_finder) override;

  // Updates a vector of a Detector type struct (i.e. list of detected objects)
  void Update(const std::string& big_image_name,
              std::vector<DetectedPlayerSpell>* detected_types) override;

  template_recognition::TemplateRecognitionManager*
      template_recognition_manager_;

 private:
  DetectedPlayerSpell fireball_prototype_;
};

}  // namespace wow
}  // namespace bot

#endif  // PLAYER_SPELL_FIREBALL_H_
