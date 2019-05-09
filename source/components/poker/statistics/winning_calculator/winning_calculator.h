#ifndef WINNING_CALCULATOR_H_
#define WINNING_CALCULATOR_H_

#include "components/poker/entities/card_def.h"
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
    double losingProbability = 0;
    player_hand_ = player_hand;
    switch (table_cards.size()) {
      case 0:
        losingProbability = GetLosingProbPreFlop();
        break;
      case 3:
        losingProbability = GetLosingProbPostFlop();
        break;
      case 4:
        losingProbability = GetLosingProbPostTurn(table_cards);
        break;
      case 5:
        losingProbability = GetLosingProbPostRiver();
        break;
      default:
        std::cerr << "table cards is an incorrect size" << std::endl;
        return 0;
    }
  }

 private:
  double GetLosingProbPreFlop() {
    // Check the cache manager
  }
  double GetLosingProbPostFlop() {
    // Check the cache manager
  }

  double GetLosingProbPostTurn(const std::vector<Card>& table_cards) {
    assert(table_cards.size() == 4);

    // The oponent cannot have any of these cards as they're already played
    std::vector<Card> opponent_card_exclusions(table_cards);
    opponent_card_exclusions.push_back(player_hand_.first_card);
    opponent_card_exclusions.push_back(player_hand_.second_card);
    HandGenerator hand_generator(opponent_card_exclusions);
    std::vector<PlayerHand> opponent_possibilities =
        hand_generator.GenerateCombinations();

    // Go through each combination
    for (const PlayerHand& opponent_hand : opponent_possibilities) {
      // Generate exclusions for the remainder of the cards. e.g. (player has 1
      // 2, op has 3 4, table is given 5 6 7 8) Find all possibilities for the
      // last slot 9, 10, 11 etc...
      std::vector<Card> remainding_table_exclusions(opponent_card_exclusions);
      remainding_table_exclusions.push_back(opponent_hand.first_card);
      remainding_table_exclusions.push_back(opponent_hand.second_card);

      // Now find winner
      TableGenerator table_generator();

      // determine who wins here
    }
  }

  double GetLosingProbPostRiver();

  PlayerHand player_hand_;
  CacheManager cache_manager_;
};

}  // namespace statistics
}  // namespace poker

#endif  // WINNING_CALCULATOR_H_
