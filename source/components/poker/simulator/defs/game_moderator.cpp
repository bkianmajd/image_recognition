#include "components/poker/simulator/defs/game_moderator.h"

/// File uses a point system to determine who wins.
namespace poker {
namespace simulator {

using Points = int;

/// Returns true when player beats opponent
bool ModeratePlayerWon(const PlayerHand& player_hand,
                       const PlayerHand& opponent_hand,
                       const std::vector<Card>& table) {
  assert(table.size() == 5);
  std::vector<Card> first_player(table);
  std::vector<Card> second_player(table);
  first_player.push_back(player_hand.first_card);
  first_player.push_back(player_hand.second_card);
  second_player.push_back(opponent_hand.first_card);
  second_player.push_back(opponent_hand.second_card);

  PointCalculator first_points(first_player);
  PointCalculator second_points(second_player);
  return first_points.GetPoints() > second_points.GetPoints();
}

}  // namespace simulator
}  // namespace poker

