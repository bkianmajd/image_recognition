#ifndef WINNING_CALCULATOR_H_
#define WINNING_CALCULATOR_H_

#include <gtest/gtest_prod.h>

#include "components/poker/entities/card_def.h"
#include "components/poker/simulator/defs/game_moderator.h"
#include "components/poker/statistics/brute_force_generator/hand_generator.h"
#include "components/poker/statistics/brute_force_generator/table_generator.h"
#include "components/poker/statistics/cache_manager/cache_manager.h"
#include "helpers/time_analyzer.h"

#include "base/optional.h"

namespace poker {
namespace statistics {

namespace {

constexpr bool kDebug = true;

std::vector<Table> GenerateTableCombinations(
    const std::vector<Card>& table_cards, TableGenerator* table_generator) {
  switch (table_cards.size()) {
    case 0:
      return table_generator->GenerateCombinations();
    case 3:
      return table_generator->GenerateCombinations(
          table_cards[0], table_cards[1], table_cards[2]);
    case 4:
      return table_generator->GenerateCombinations(
          table_cards[0], table_cards[1], table_cards[2], table_cards[3]);
    case 5:
      break;
    default:
      std::cerr << "This should not be called" << std::endl;
      assert(false);
  }

  // There are no combos when there are already five cards presented on the
  // table
  std::vector<Table> single_table_combo;
  single_table_combo.push_back(Table(table_cards[0], table_cards[1],
                                     table_cards[2], table_cards[3],
                                     table_cards[4]));
  return single_table_combo;
}

double CalculateLosingProbability(const PlayerHand& player_hand,
                                  const std::vector<Card>& table_cards) {
  // The oponent cannot have any of these cards as they're already played
  std::vector<Card> opponent_card_exclusions;
  opponent_card_exclusions.assign(table_cards.begin(), table_cards.end());
  opponent_card_exclusions.push_back(player_hand.FirstCard());
  opponent_card_exclusions.push_back(player_hand.SecondCard());

  // Generate all possibilities of the opponents hand
  HandGenerator hand_generator(opponent_card_exclusions);
  std::vector<PlayerHand> opponent_possibilities =
      hand_generator.GenerateCombinations();

  // Setup the counter
  int total_count = 0;
  int losing_count = 0;

  int opponent_hand_progression = 0;

  // Go through each combination
  for (const PlayerHand& opponent_hand : opponent_possibilities) {
    // Generate exclusions for the remainder of the cards. e.g. (player has 1
    // 2, op has 3 4, table is given 5 6 7 8 ) Find all possibilities for the
    // last slot 9, 10, 11 etc...
    std::vector<Card> remainding_table_exclusions(opponent_card_exclusions);
    remainding_table_exclusions.push_back(opponent_hand.FirstCard());
    remainding_table_exclusions.push_back(opponent_hand.SecondCard());

    // Generate all the combinations for the table given the first three cards
    TableGenerator table_generator(remainding_table_exclusions);
    std::vector<Table> table_combos =
        GenerateTableCombinations(table_cards, &table_generator); // this takes a long time

    // debug statement here to look at the progression of the for loops
    if (kDebug) {
      std::cout << "Opponent hand: " << opponent_hand_progression++
                << " out of " << opponent_possibilities.size() << " Table size "
                << table_combos.size() << std::endl;
    }

    // Now find winner
    for (const Table& table : table_combos) {
      TIME_ANALYZE(simulator::GameResult game_result =
                       simulator::ModeratePlayerWon(player_hand, opponent_hand, table))
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

}  // namespace

/// Calculates the probability given a players hand
class WinningCalculator {
 public:
  WinningCalculator(CacheManager* cache_manager)
      : cache_manager_(cache_manager), initialized_(false) {}

  double GetWinningProbability(const PlayerHand& player_hand,
                               const std::vector<Card>& table_cards,
                               int opponents) {
    if (!initialized_) {
      cache_manager_->InitializeLoad();
      initialized_ = true;
    }

    // reset state
    double losingProbability = 0;

    switch (table_cards.size()) {
      case 0:
        losingProbability = GetLosingProbPreFlop(player_hand);
        break;
      case 3:
        losingProbability = GetLosingProbPostFlop(player_hand, table_cards);
        break;
      case 4:
        losingProbability =
            CalculateLosingProbability(player_hand, table_cards);
        break;
      case 5:
        losingProbability =
            CalculateLosingProbability(player_hand, table_cards);
        break;
      default:
        std::cerr << "table cards is an incorrect size" << std::endl;
        return 0;
    }

    return 1 - (losingProbability * opponents);
  }

 private:
  double GetLosingProbPreFlop(const PlayerHand& player_hand) {
    base::Optional<double> result =
        cache_manager_->GetLosingProbability(player_hand);
    if (result.has_value()) {
      return result.value();
    }
    double losing_probability =
        CalculateLosingProbability(player_hand, std::vector<Card>());
    cache_manager_->StoreLosingProbability(player_hand, losing_probability);
    return losing_probability;
  }

  double GetLosingProbPostFlop(const PlayerHand& player_hand,
                               const std::vector<Card>& table_cards) {
    std::vector<Card> player_cards{player_hand.FirstCard(),
                                   player_hand.SecondCard()};
    base::Optional<double> result =
        cache_manager_->GetLosingProbability(player_cards, table_cards);
    if (result.has_value()) {
      return result.value();
    }
    double losing_probability =
        CalculateLosingProbability(player_hand, std::vector<Card>());
    cache_manager_->StoreLosingProbability(player_cards, table_cards,
                                           losing_probability);
    return losing_probability;
  }

  CacheManager* cache_manager_;
  bool initialized_;
};

}  // namespace statistics
}  // namespace poker

#endif  // WINNING_CALCULATOR_H_
