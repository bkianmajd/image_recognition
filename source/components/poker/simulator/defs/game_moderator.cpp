#include "components/poker/simulator/defs/game_moderator.h"

/// File uses a point system to determine who wins.
namespace poker {
namespace simulator {
namespace {

}  // namespace

using Points = int;

/// Returns true when player beats opponent
GameResult ModeratePlayerWon(const PlayerHand& player_hand,
                             const PlayerHand& opponent_hand,
                             const Table& table) {
  CardCombo player(player_hand, table);
  CardCombo opponent(opponent_hand, table);
// avoid a copy by passing player_hand and table into point calculator directly
  PointCalculator player_calculator(player.cards_);
  PointCalculator opponent_calculator(opponent.cards_);
  Points player_points = player_calculator.GetPoints();
  Points opponent_points = opponent_calculator.GetPoints();
  if (player_points < opponent_points) {
    return GAME_RESULT_LOST;
  }
  if (player_points > opponent_points) {
    return GAME_RESULT_WIN;
  }
  return GAME_RESULT_TIE;
}

}  // namespace simulator
}  // namespace poker
