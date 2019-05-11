#include "components/poker/simulator/defs/game_moderator.h"

/// File uses a point system to determine who wins.
namespace poker {
namespace simulator {
namespace {

inline void PopulateSevenCards(const PlayerHand& player_hand,
                               const Table& table, std::vector<Card>* player) {
  player->at(0) = player_hand.first_card;
  player->at(1) = player_hand.second_card;
  player->at(2) = table.first_card;
  player->at(3) = table.second_card;
  player->at(4) = table.third_card;
  player->at(5) = table.fourth_card;
  player->at(6) = table.fifth_card;
}

}  // namespace

using Points = int;

/// Returns true when player beats opponent
GameResult ModeratePlayerWon(const PlayerHand& player_hand,
                             const PlayerHand& opponent_hand,
                             const Table& table) {
  assert(table.table_state == TABLE_STATE_RIVER);
  std::vector<Card> player(7);
  std::vector<Card> opponent(7);

  PopulateSevenCards(player_hand, table, &player);
  PopulateSevenCards(opponent_hand, table, &opponent);

  PointCalculator player_calculator(player);
  PointCalculator opponent_calculator(opponent);
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
