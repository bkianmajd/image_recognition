#ifndef GAME_MODEL_DEF_H_
#define GAME_MODEL_DEF_H_

#include <array>
#include <string>
#include <vector>

#include "components/poker/entities/card_def.h"
#include "components/poker/entities/player_location_def.h"

namespace poker {

/// @struct GameStatus
/// Entity
/// Contains the temporal information for a single game
struct GameStatus {
  int number_of_chairs;
};

struct GameModel {
  GameStatus game_status;
  std::array<PlayerHand, PLAYERLOC_MAXSIZE> player_hands;
  std::array<Card, DEALER_MAX_SIZE> dealer_cards;
};

}  // poker

#endif  // GAME_MODEL_DEF_H_
