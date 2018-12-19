#ifndef AREA_FINDER_H_
#define AREA_FINDER_H_

#include "components/poker/entities/player_location_def.h"
#include "libraries/screenshot_creator/screenshot_creator.h"

namespace poker {

class AreaFinder {
 public:
  ~AreaFinder() = default;

  // Gets an area of the chair of each player
  template_recognition::ScreenArea virtual GetPlayerArea(PlayerLocation) = 0;

  // gets the area of each player's bank roll
  template_recognition::ScreenArea virtual GetMoneyArea(PlayerLocation) = 0;

  // Gets table landmarks like pot, dealer chip
  template_recognition::ScreenArea virtual GetTableArea(PlayerLocation) = 0;

  // Gets the left card of this player
  template_recognition::ScreenArea virtual GetCardAreaLeft(PlayerLocation) = 0;
  // Gets the right card of this player
  template_recognition::ScreenArea virtual GetCardAreaRight(PlayerLocation) = 0;

  // Gets the card on the table dealt by the dealer
  template_recognition::ScreenArea GetDealerCard(
      DealerLocation dealer_location) {
    template_recognition::ScreenArea screen_area;
    screen_area.width = kDefaultCardWidth;
    screen_area.height = kDefaultCardHeight;
    screen_area.y = 220;

    switch (dealer_location) {
      case DEALER_ONE:
        screen_area.x = 340;
        break;
      case DEALER_TWO:
        screen_area.x = 415;
        break;
      case DEALER_THREE:
        screen_area.x = 489;
        break;
      case DEALER_FOUR:
        screen_area.x = 564;
        break;
      case DEALER_FIVE:
        screen_area.x = 638;
        break;
      default:
        screen_area.height = 0;
        screen_area.width = 0;
        break;
    }
    return screen_area;
  }

 protected:
  // For Card area
  static constexpr int kDefaultCardWidth = 62;
  static constexpr int kDefaultCardHeight = 50;
  static constexpr int kDefaultPlayerWidth = 137;
  static constexpr int kDefaultPlayerHeight = 29;
};

}  // namespace poker

#endif  // AREA_FINDER_H_
