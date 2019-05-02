#include "generic_bot/wow/sensor/wow_detectors/player_spell_fireball.h"

#include "helpers/file_manager.h"

namespace bot {
namespace wow {
namespace {
const std::string kFireballImage = "fireball.jpg";
}  // namespace

PlayerSpellFireball::PlayerSpellFireball(
    template_recognition::TemplateRecognitionManager*
        template_recognition_manager)
    : template_recognition_manager_(template_recognition_manager) {
  fireball_prototype_.player_spell = PlayerSpell::PLAYER_SPELL_FIREBALL;
}

bool PlayerSpellFireball::RegisterTemplateImages(
    const helpers::DirectoryFinder& directory_finder) {
  std::string template_image_name =
      directory_finder.GetAbsPathOfTargetFile(kFireballImage);

  // Grab the raw data
  std::vector<char> raw_data =
      helpers::FileManager::ReadFile(template_image_name);

  if (raw_data.size() == 0) {
    std::cerr << "Raw data size = 0 " << template_image_name << std::endl;
    return false;
  }

  // Store the image
  if (!template_recognition_manager_->StoreImage(kFireballImage, raw_data)) {
    std::cerr << "Failed to store image " << template_image_name << std::endl;
    return false;
  }
}

void PlayerSpellFireball::Update(
    const std::string& big_image_name,
    std::vector<DetectedPlayerSpell>* detected_types) {
  template_recognition::Point point;
  if (!template_recognition_manager_->TemplateMatch(big_image_name,
                                                    kFireballImage, &point)) {
    std::cerr << "PlayerSpellFireball: Failed to reg point" << std::endl;
    return;
  }

  if (!point.isValid) {
    return;
  }

  fireball_prototype_.point.x_location = point.x;
  fireball_prototype_.point.y_location = point.y;
  detected_types->push_back(fireball_prototype);
}

}  // bot
}  // wow
