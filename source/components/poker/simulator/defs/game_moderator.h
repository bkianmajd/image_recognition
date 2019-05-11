#ifndef GAME_MODERATOR_H_
#define GAME_MODERATOR_H_

#include <algorithm>
#include <cassert>

#include "components/poker/entities/card_def.h"
#include "components/poker/simulator/defs/point_calculator.h"

/// File uses a point system to determine who wins.
namespace poker {
namespace simulator {

using Points = int;

/// Returns true when player beats opponent
bool ModeratePlayerWon(const PlayerHand& player_hand,
                       const PlayerHand& opponent_hand,
                       const std::vector<Card>& table);

}  // namespace simulator
}  // namespace poker

#endif  // GAME_MODERATOR_H_
