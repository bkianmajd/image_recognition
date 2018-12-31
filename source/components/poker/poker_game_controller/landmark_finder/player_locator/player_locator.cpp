#include "components/poker/poker_game_controller/landmark_finder/player_locator/player_locator.h"

#include <cstdint>

namespace poker {
namespace {
constexpr int kDefaultWidth = 165;
constexpr int kDefaultHeight = 90;
constexpr int kLeftCardOffsetX = 30;
constexpr int kLeftCardOffsetY = 0;
constexpr int kDefaultCardWidth = 50;
constexpr int kDefaultCardHeight = 45;
constexpr int kRightCardOffsetX = kLeftCardOffsetX + kDefaultCardWidth - 2;
constexpr int kRightCardOffsetY = kLeftCardOffsetY;

std::pair<int, int> GetSixPlayerReference(PlayerLocation player_location) {
  /*
   *           x_2, ---
   * x_1,y_1                  x_3,y_1
   * x_1,y_2                  x_3,y_2
   *           x_2, ---
  */
  int x_axis_first = 30;
  int x_axis_second = 327;
  int x_axis_third = 625;

  int y_axis_first = 113;
  int y_axis_second = 285;

  switch (player_location) {
    case PLAYERLOC_PLAYER_ZERO:
      return std::make_pair(x_axis_second - 1, 381);
    case PLAYERLOC_PLAYER_ONE:
      return std::make_pair(x_axis_first, y_axis_first);
    case PLAYERLOC_PLAYER_TWO:
      return std::make_pair(x_axis_first, y_axis_second);
    case PLAYERLOC_PLAYER_THREE:
      return std::make_pair(x_axis_second, 47);
    case PLAYERLOC_PLAYER_FOUR:
      return std::make_pair(x_axis_third, y_axis_first);
    case PLAYERLOC_PLAYER_FIVE:
      return std::make_pair(x_axis_third, y_axis_second);
    default:
      std::cerr << "can only process six areas" << std::endl;
      assert(false);
  }

  return std::make_pair<int, int>(0, 0);
}
}  // namespace

PlayerLocator::PlayerLocator(int table_size, PlayerLocation player_location) {
  std::pair<int, int> player_reference;
  switch (table_size) {
    case 6:
      player_reference = GetSixPlayerReference(player_location);
      break;
    default:
      std::cerr << "Table size is not valid" << std::endl;
      assert(false);
  }
  x_reference_ = player_reference.first;
  y_reference_ = player_reference.second;
}

template_recognition::ScreenArea PlayerLocator::GetPlayerArea() const {
  return template_recognition::ScreenArea(x_reference_, y_reference_,
                                          kDefaultWidth, kDefaultHeight);
}
template_recognition::ScreenArea PlayerLocator::GetLeftCardArea() const {
  return template_recognition::ScreenArea(
      x_reference_ + kLeftCardOffsetX, y_reference_ + kLeftCardOffsetY,
      kDefaultCardWidth, kDefaultCardHeight);
}
template_recognition::ScreenArea PlayerLocator::GetRightCardArea() const {
  return template_recognition::ScreenArea(
      x_reference_ + kRightCardOffsetX, y_reference_ + kRightCardOffsetY,
      kDefaultCardWidth, kDefaultCardHeight);
}

}  // namespace poker
