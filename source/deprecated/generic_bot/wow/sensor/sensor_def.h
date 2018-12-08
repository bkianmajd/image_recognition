#ifndef WOW_SENSOR_DEF_
#define WOW_SENSOR_DEF_

namespace bot {
namespace wow {

enum ImageType {
  IMAGE_TYPE_NONE = 0,
  IMAGE_TYPE_ENEMY,
  IMAGE_TYPE_NPC,
  IMAGE_TYPE_MOB,
  IMAGE_TYPE_PLAYER_SPELL,
};

struct PixelPoint {
  int x_location;
  int y_location;
};

enum Enemy {
  ENEMY_HOSTILE = 0,
  ENEMY_NON_HOSTILE,
};

enum PlayerSpell {
  PLAYER_SPELL_FIREBALL = 0,
  PLAYER_SPELL_FROSTBOLT,
  PLAYER_SPELL_FIREBLAST,
  PLAYER_SPELL_CONEOFCOLD,
  PLAYER_SPELL_FROSTNOVA,
  PLAYER_SPELL_ARCANEMISSILES,
  PLAYER_SPELL_POLYMORPH,
};

struct DetectedObject {
  PixelPoint point;
  ImageType image_type;

  PlayerSpell player_spell;
};

}  // namespace wow
}  // namespace bot

#endif  // WOW_SENSOR_DEF_
