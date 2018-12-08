#ifndef AREA_FINDER_H_
#define AREA_FINDER_H_

#include "components/poker/entities/player_location_def.h"
#include "libraries/screenshot_creator/screenshot_creator.h"

namespace poker {

class AreaFinder {
 public:
  ~AreaFinder() = default;

  template_recognition::ScreenArea virtual GetPlayerArea(PlayerLocation) = 0;
  template_recognition::ScreenArea virtual GetMoneyArea(PlayerLocation) = 0;
  template_recognition::ScreenArea virtual GetTableArea(PlayerLocation) = 0;

  // Gets the left card of this player
  template_recognition::ScreenArea virtual GetCardAreaLeft(PlayerLocation) = 0;
  // Gets the right card of this player
  template_recognition::ScreenArea virtual GetCardAreaRight(PlayerLocation) = 0;

  // Gets the card on the table dealt by the dealer
  template_recognition::ScreenArea GetDealerCard(
      DealerLocation dealer_location) {
    template_recognition::ScreenArea screen_area;
    switch (dealer_location) {
      case DEALER_NONE:
        break;
      case DEALER_ONE:
        break;
      case DEALER_TWO:
        break;
      case DEALER_THREE:
        break;
      case DEALER_FOUR:
        break;
      case DEALER_FIVE:
        break;
      default:
        break;
    }
    return screen_area;
  }

 protected:
  // For Card area
  static constexpr int kDefaultCardWidth = 58;
  static constexpr int kDefaultCardHeight = 48;
  static constexpr int kDefaultPlayerWidth = 137;
  static constexpr int kDefaultPlayerHeight = 29;
};

}  // namespace poker

#endif  // AREA_FINDER_H_
