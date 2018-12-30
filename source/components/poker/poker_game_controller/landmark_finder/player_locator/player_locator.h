#ifndef PLAYER_LOCATOR_H_
#define PLAYER_LOCATOR_H_

#include <cassert>

#include "components/poker/entities/player_location_def.h"
#include "libraries/screenshot_creator/screenshot_creator.h"

namespace poker {

/// Returns the area of the features on the player
class PlayerLocator {
 public:
  PlayerLocator(int table_size, PlayerLocation player_location);

  template_recognition::ScreenArea GetPlayerArea() const;
  template_recognition::ScreenArea GetLeftCardArea() const;
  template_recognition::ScreenArea GetRightCardArea() const;

 private:
  int x_reference_;
  int y_reference_;
};

}  // namespace poker

#endif  // PLAYER_LOCATOR_H_
