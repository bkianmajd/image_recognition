#ifndef GAME_MODERATOR_H_
#define GAME_MODERATOR_H_

#include <algorithm>
#include <cassert>

#include "components/poker/entities/card_def.h"

/// File uses a point system to determine who wins.
namespace poker {
namespace simulator {

using Points = int;

// Assume sorting
namespace {

bool HasRoyalFlush() {}

// Returns a relative number of points based on the ranking of poker hands
int GetPointsFrom5(const std::vector<Card>& formulated_hand) {
  assert(formulated_hand.size() == 5);
  if(HasRoyalFlush()) {
    return 1000;
  }
  //if(HasFlush() && HasStrightFLush())

  //}

}  // namespace



/// Returns true when player beats opponent
bool ModeratePlayerWon(const PlayerHand& player_hand,
                       const PlayerHand& opponent_hand,
                       const std::vector<Card>& table) {
  assert(table.size() == 5)
}

}  // namespace simulator
}  // namespace poker

#endif  // GAME_MODERATOR_H_
