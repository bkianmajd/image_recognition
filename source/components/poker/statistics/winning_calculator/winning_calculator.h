#ifndef WINNING_CALCULATOR_H_
#define WINNING_CALCULATOR_H_

#include <gtest/gtest_prod.h>

#include "components/poker/entities/card_def.h"
#include "components/poker/simulator/defs/game_moderator.h"
#include "components/poker/statistics/brute_force_generator/hand_generator.h"
#include "components/poker/statistics/brute_force_generator/table_generator.h"
#include "components/poker/statistics/cache_manager/cache_manager.h"

namespace poker {
namespace statistics {

const std::string kCacheDir =
    "components/poker/statistics/cache_manager/binary_data";
const std::string kGenericPreflopCache = "genericPreflop.dat";
const std::string kGenericPostflopCache = "genericPostflop.dat";

/// Calculates the probability given a players hand
class WinningCalculator {
 public:
  WinningCalculator()
      : cache_manager_(helpers::CreateDirectoryFinderFromWorkspace(kCacheDir),
                       kGenericPreflopCache, kGenericPostflopCache) {}

  double GetWinningProbability(const PlayerHand& player_hand,
                               const std::vector<Card>& table_cards,
                               int opponents) {
    // reset state
    double losingProbability = 0;
    opponent_card_exclusions_.clear();
    player_hand_ = player_hand;

    // The oponent cannot have any of these cards as they're already played
    opponent_card_exclusions_.assign(table_cards.begin(), table_cards.end());
    opponent_card_exclusions_.push_back(player_hand_.first_card);
    opponent_card_exclusions_.push_back(player_hand_.second_card);

    HandGenerator hand_generator(opponent_card_exclusions_);
    opponent_possibilities_ = hand_generator.GenerateCombinations();

    switch (table_cards.size()) {
      case 0:
        losingProbability = GetLosingProbPreFlop();
        break;
      case 3:
        losingProbability = GetLosingProbPostFlop(table_cards);
        break;
      case 4:
        losingProbability = GetLosingProbPostTurn(table_cards);
        break;
      case 5:
        losingProbability = GetLosingProbPostRiver(table_cards);
        break;
      default:
        std::cerr << "table cards is an incorrect size" << std::endl;
        return 0;
    }

    return 1 - (losingProbability * opponents);
  }

 private:
  double GetLosingProbPreFlop() {
    // Check the cache manager
  }
  double GetLosingProbPostFlop(const std::vector<Card>& table_cards) {
    assert(table_cards.size() == 3);
    // Check the cache manager
  }

  double GetLosingProbPostRiver(const std::vector<Card>& table_cards) const {
    assert(table_cards.size() == 5);

    // Setup the counter
    int total_count = 0;
    int losing_count = 0;
    Table table(table_cards[0], table_cards[1], table_cards[2], table_cards[3],
                table_cards[4]);

    // Go through each combination
    for (const PlayerHand& opponent_hand : opponent_possibilities_) {
      simulator::GameResult game_result =
          simulator::ModeratePlayerWon(player_hand_, opponent_hand, table);
      if (game_result == simulator::GAME_RESULT_LOST) {
        losing_count++;
      }
      if (game_result != simulator::GAME_RESULT_TIE) {
        total_count++;
      }
    }

    return static_cast<double>(losing_count) / static_cast<double>(total_count);
  }

  double GetLosingProbPostTurn(const std::vector<Card>& table_cards) {
    assert(table_cards.size() == 4);

    // Setup the counter
    int total_count = 0;
    int losing_count = 0;

    // Go through each combination
    for (const PlayerHand& opponent_hand : opponent_possibilities_) {
      // Generate exclusions for the remainder of the cards. e.g. (player has 1
      // 2, op has 3 4, table is given 5 6 7 8 ) Find all possibilities for the
      // last slot 9, 10, 11 etc...
      std::vector<Card> remainding_table_exclusions(opponent_card_exclusions_);
      remainding_table_exclusions.push_back(opponent_hand.first_card);
      remainding_table_exclusions.push_back(opponent_hand.second_card);

      // Generate all the combinations for the table given the first four cards
      TableGenerator table_generator(remainding_table_exclusions);
      std::vector<Table> table_combos = table_generator.GenerateCombinations(
          table_cards[0], table_cards[1], table_cards[2], table_cards[3]);

      // Now find winner
      for (const Table& table : table_combos) {
        simulator::GameResult game_result =
            simulator::ModeratePlayerWon(player_hand_, opponent_hand, table);
        if (game_result == simulator::GAME_RESULT_LOST) {
          losing_count++;
        }
        if (game_result != simulator::GAME_RESULT_TIE) {
          total_count++;
        }
      }
    }
    return static_cast<double>(losing_count) / static_cast<double>(total_count);
  }

  PlayerHand player_hand_;
  std::vector<Card> opponent_card_exclusions_;
  std::vector<PlayerHand> opponent_possibilities_;
  CacheManager cache_manager_;
};

}  // namespace statistics
}  // namespace poker

#endif  // WINNING_CALCULATOR_H_
