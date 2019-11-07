#include "components/poker/statistics/hand_calculator/hand_calculator.h"

#include "components/poker/entities/card_def.h"
#include "components/poker/simulator/defs/game_moderator.h"
#include "components/poker/statistics/brute_force_generator/hand_generator.h"
#include "components/poker/statistics/brute_force_generator/table_generator.h"
#include "components/poker/statistics/defs/defs.h"
#include "helpers/time_analyzer.h"
#include "libraries/protobuf_loader/cache_manager.h"

#include "components/poker/statistics/cache_storage/proto/poker_statistics.pb.h"

#include "base/optional.h"

namespace poker {
namespace statistics {

namespace {

constexpr bool kDebug = true;
constexpr bool kReadOnly = true;
const std::string kCacheDirectory =
    "components/poker/statistics/cache_storage/binary_data";

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

HandStatistic CalculateLosingProbability(const PlayerHand& player_hand,
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
  uint64_t total_count = 0;
  uint64_t losing_count = 0;
  uint64_t tieing_count = 0;

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
        GenerateTableCombinations(table_cards, &table_generator);

    // Now find winner
    for (const Table& table : table_combos) {
      simulator::GameResult game_result =
          simulator::ModeratePlayerWon(player_hand, opponent_hand, table);
      if (game_result == simulator::GAME_RESULT_LOST) {
        losing_count++;
      }
      if (game_result == simulator::GAME_RESULT_TIE) {
        tieing_count++;
      }
      total_count++;
    }
  }

  HandStatistic hand_statistic;
  hand_statistic.losing_probability =
      static_cast<double>(losing_count) / static_cast<double>(total_count);
  hand_statistic.tie_probability =
      static_cast<double>(tieing_count) / static_cast<double>(total_count);
  return hand_statistic;
}

}  // namespace

/// Calculates the probability given a players hand

HandCalculator::HandCalculator()
    : cache_manager_(
          helpers::CreateDirectoryFinderFromWorkspace(kCacheDirectory),
          kReadOnly) {}

HandStatistic HandCalculator::CalculateHandProbability(
    const PlayerHand& player_hand, const Table& table, int opponents) {
  HandStatistic hand_statistic;
  // move table into a vector
  std::vector<Card> table_cards;
  for (const Card& card : table.cards_) {
    if (card.value == CARD_VALUE_HIDDEN || card.suit == SUIT_HIDDEN) {
      continue;
    }
    if (card.value == CARD_VALUE_UNKNOWN || card.suit == SUIT_UNKNOWN) {
      continue;
    }

    table_cards.push_back(card);
  }

  // reset state
  hand_statistic.losing_probability = 0;
  hand_statistic.tie_probability = 0;

  switch (table_cards.size()) {
    case 0:
      hand_statistic = GetHandStatisticPreFlop(player_hand);
      break;
    case 3:
      // fall-through
    case 4:
      // fall-through
    case 5:
      hand_statistic = CalculateLosingProbability(player_hand, table_cards);
      break;
    default:
      std::cerr << "table cards is an incorrect size" << std::endl;
      assert(false);
  }

  // Assume tie probability stays the same despite # of opponents
  // losing probability increases
  hand_statistic.losing_probability =
      hand_statistic.losing_probability * static_cast<double>(opponents);
  return hand_statistic;
}

HandStatistic HandCalculator::GetHandStatisticPreFlop(
    const PlayerHand& player_hand) {
  // access the cache manager for this
  poker::PreFlopStatistic* pre_flop_proto = cache_manager_.Get();
  auto& map = pre_flop_proto->losing_probability_map();
  auto it = map.find(player_hand.UniqueId());

  if (map.size() == 0 || it == map.end()) {
    // This should not happen, map should be full of all combinations
    assert(true);
  }
  const poker::Statistic& statistic = it->second;
  HandStatistic hand_statistic;
  hand_statistic.tie_probability = statistic.tie_probability();
  hand_statistic.losing_probability = statistic.losing_probability();
  return hand_statistic;
}

}  // namespace statistics
}  // namespace poker
