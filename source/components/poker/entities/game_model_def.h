#ifndef GAME_MODEL_DEF_H_
#define GAME_MODEL_DEF_H_

#include <array>
#include <string>
#include <vector>

#include "components/poker/entities/card_def.h"
#include "components/poker/entities/player_location_def.h"

namespace poker {

enum PlayerStatus {
  PLAYER_STATUS_UNKNOWN = 0,
  PLAYER_STATUS_IN_HAND,
  PLAYER_STATUS_FOLDED,
  PLAYER_STATUS_OUTSIDE,
};

enum TableStatus {
  TABLE_STATUS_UNKNOWN = 0,
  TABLE_STATUS_PREFLOP,
  TABLE_STATUS_FLOP,
  TABLE_STATUS_TURN,
  TABLE_STATUS_RIVER,
};

/// @struct GameStatus
/// Entity
/// Contains the temporal information for a single game
struct GameStatus {
  std::array<PlayerStatus, PLAYERLOC_MAXSIZE> player_status;
  TableStatus table_status;
};

struct GameModel {
  GameStatus game_status;
  std::array<PlayerHand, PLAYERLOC_MAXSIZE> player_cards;
  std::array<Card, TABLE_STATUS_RIVER> dealer_cards;
};

}  // poker

#endif  // GAME_MODEL_DEF_H_
