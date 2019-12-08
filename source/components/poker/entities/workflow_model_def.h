#ifndef WORKFLOW_MODEL_DEF_H_
#define WORKFLOW_MODEL_DEF_H_

#include <array>
#include <string>
#include <vector>

#include "components/poker/entities/card_def.h"
#include "components/poker/entities/player_location_def.h"

namespace poker {

enum WorkflowState {
  UNKNOWN = -1,
  PREFLOP =0,
  FLOP = 3,
  TURN = 4,
  RIVER = 5,
};

/// @struct GameStatus
/// Contains the information for a single game
// TODO(BK): Put in bet information by respective player
struct WorkflowModel {
  WorkflowState workflow_state;
  int number_of_original_opponents = 0;
  int number_of_active_opponents = 0;
  bool in_hand;
  std::array<Card, DEALER_MAX_SIZE> dealer_cards;
  PlayerHand player_hand;
};

}  // namespace poker

#endif  // WORKFLOW_MODEL_DEF_H_
