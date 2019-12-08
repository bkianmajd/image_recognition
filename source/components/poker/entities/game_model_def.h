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

namespace model {
inline int NumberOfActiveOponents(const GameModel& game_model) {
  int numOfOponents = 0;
  for (size_t i = 0; i < PLAYERLOC_MAXSIZE; ++i) {
    if (i == 0) {
      continue;
    }
    if (game_model.player_hands[i].FirstCard().suit == SUIT_UNKNOWN) {
      continue;
    }
    numOfOponents++;
  }
  return numOfOponents;
}

}  // namespace model
}  // namespace poker

#endif  // GAME_MODEL_DEF_H_
