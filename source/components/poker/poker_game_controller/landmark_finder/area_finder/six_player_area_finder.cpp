#include "components/poker/poker_game_controller/landmark_finder/area_finder/six_player_area_finder.h"

namespace poker {
namespace {

template_recognition::ScreenArea ErrorScreenArea() {
  std::cerr << "SixPlayerScreenArea: input player location out of bounds"
            << std::endl;
  return template_recognition::ScreenArea(0, 0, 0, 0);
}

}  // namespace

template_recognition::ScreenArea SixPlayerAreaFinder::GetPlayerArea(
    PlayerLocation player_location) {
  switch (player_location) {
    case PlayerLocation::PLAYERLOC_PLAYER_ZERO:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_ONE:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_TWO:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_THREE:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_FOUR:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_FIVE:
      break;
    default:
      return ErrorScreenArea();
  }
  return ErrorScreenArea();
}

template_recognition::ScreenArea SixPlayerAreaFinder::GetCardAreaLeft(
    PlayerLocation player_location) {
  switch (player_location) {
    case PlayerLocation::PLAYERLOC_PLAYER_ZERO:
      return template_recognition::ScreenArea(457, 431, kDefaultCardWidth,
                                              kDefaultCardHeight);
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_ONE:
      return template_recognition::ScreenArea(68, 322, kDefaultCardWidth,
                                              kDefaultCardHeight);
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_TWO:
      return template_recognition::ScreenArea(68, 97, kDefaultCardWidth,
                                              kDefaultCardHeight);
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_THREE:
      return template_recognition::ScreenArea(458, 11, kDefaultCardWidth,
                                              kDefaultCardHeight);
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_FOUR:
      return template_recognition::ScreenArea(851, 98, kDefaultCardWidth,
                                              kDefaultCardHeight);
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_FIVE:
      return template_recognition::ScreenArea(851, 324, kDefaultCardWidth,
                                              kDefaultCardHeight);
      break;
    default:
      return ErrorScreenArea();
  }
  return ErrorScreenArea();
}

template_recognition::ScreenArea SixPlayerAreaFinder::GetCardAreaRight(
    PlayerLocation player_location) {
  switch (player_location) {
    case PlayerLocation::PLAYERLOC_PLAYER_ZERO:
      return template_recognition::ScreenArea(523, 431, kDefaultCardWidth,
                                              kDefaultCardHeight);

      break;
    case PlayerLocation::PLAYERLOC_PLAYER_ONE:
      return template_recognition::ScreenArea(133, 322, kDefaultCardWidth,
                                              kDefaultCardHeight);

      break;
    case PlayerLocation::PLAYERLOC_PLAYER_TWO:
      return template_recognition::ScreenArea(133, 97, kDefaultCardWidth,
                                              kDefaultCardHeight);

      break;
    case PlayerLocation::PLAYERLOC_PLAYER_THREE:
      return template_recognition::ScreenArea(523, 13, kDefaultCardWidth,
                                              kDefaultCardHeight);

      break;
    case PlayerLocation::PLAYERLOC_PLAYER_FOUR:
      return template_recognition::ScreenArea(915, 99, kDefaultCardWidth,
                                              kDefaultCardHeight);

      break;
    case PlayerLocation::PLAYERLOC_PLAYER_FIVE:
      return template_recognition::ScreenArea(917, 324, kDefaultCardWidth,
                                              kDefaultCardHeight);

      break;
    default:
      return ErrorScreenArea();
  }
  return ErrorScreenArea();
}

template_recognition::ScreenArea SixPlayerAreaFinder::GetMoneyArea(
    PlayerLocation player_location) {
  switch (player_location) {
    case PlayerLocation::PLAYERLOC_PLAYER_ZERO:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_ONE:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_TWO:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_THREE:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_FOUR:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_FIVE:
      break;
    default:
      return ErrorScreenArea();
  }
  return ErrorScreenArea();
}

template_recognition::ScreenArea SixPlayerAreaFinder::GetTableArea(
    PlayerLocation player_location) {
  switch (player_location) {
    case PlayerLocation::PLAYERLOC_PLAYER_ZERO:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_ONE:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_TWO:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_THREE:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_FOUR:
      break;
    case PlayerLocation::PLAYERLOC_PLAYER_FIVE:
      break;
    default:
      return ErrorScreenArea();
  }
  return ErrorScreenArea();
}

}  // namespace poker
