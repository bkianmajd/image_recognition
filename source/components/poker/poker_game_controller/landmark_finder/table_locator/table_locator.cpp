#include "components/poker/poker_game_controller/landmark_finder/table_locator/table_locator.h"

namespace poker {
namespace {

constexpr int kDefaultCardWidth = 50;
constexpr int kDefaultCardHeight = 45;
constexpr int kDefaultDealerLocX = 273;
constexpr int kDefaultDealerLocY = 222;
constexpr int kOffset = 4;

}  // namespace

TableLocator::TableLocator(int table_size) : table_size_(table_size) {
  // TODO() : add more table sizes
  assert(table_size == 6);
}

template_recognition::ScreenArea TableLocator::GetDealerArea(
    DealerLocation dealer_location) const {
  template_recognition::ScreenArea screen_area;
  screen_area.width = kDefaultCardWidth;
  screen_area.height = kDefaultCardHeight;
  screen_area.y = kDefaultDealerLocY;

  switch (dealer_location) {
    case DEALER_ONE:
      screen_area.x =
          kDefaultDealerLocX +
          (static_cast<int>(DEALER_ONE) - 1) * (kDefaultCardWidth + kOffset);
      break;
    case DEALER_TWO:
      screen_area.x =
          kDefaultDealerLocX +
          (static_cast<int>(DEALER_TWO) - 1) * (kDefaultCardWidth + kOffset);
      break;
    case DEALER_THREE:
      screen_area.x =
          kDefaultDealerLocX +
          (static_cast<int>(DEALER_THREE) - 1) * (kDefaultCardWidth + kOffset);
      break;
    case DEALER_FOUR:
      screen_area.x =
          kDefaultDealerLocX +
          (static_cast<int>(DEALER_FOUR) - 1) * (kDefaultCardWidth + kOffset);
      break;
    case DEALER_FIVE:
      screen_area.x =
          kDefaultDealerLocX +
          (static_cast<int>(DEALER_FIVE) - 1) * (kDefaultCardWidth + kOffset);
      break;
    default:
      std::cerr << "Dealer location invalid" << std::endl;
      screen_area.height = 0;
      screen_area.width = 0;
      break;
  }
  return screen_area;
}

template_recognition::ScreenArea TableLocator::GetPotArea() const {
  // TODO() : impliment this
  return template_recognition::ScreenArea();
}

template_recognition::ScreenArea TableLocator::GetDealerPuck(
    PlayerLocation player_location) const {
  switch (player_location) {
    case PlayerLocation::PLAYERLOC_PLAYER_SIX:
      return GetDealerPuck6();
    default:
      break;
  }

  // Technically shouldn't be reached
  assert(false);
  return template_recognition::ScreenArea();
}

template_recognition::ScreenArea TableLocator::GetDealerPuck6() const {
  // TODO() : impliment this
  return template_recognition::ScreenArea();
}

}  // namespace poker
