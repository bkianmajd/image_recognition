#include "components/poker/statistics/brute_force_generator/table_generator.h"

#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include "components/poker/statistics/brute_force_generator/hand_generator.h"
#include "helpers/time_analyzer.h"

namespace poker {
namespace statistics {
namespace {
// Generates a unique Id from the first 3 cards
unsigned long GenerateFirstUniqueId(const std::array<int, 5>& sorted_array) {
  std::stringstream ss;
  // Converts a vector of cards to a specific id of x digits.
  ss << sorted_array[0];
  ss << sorted_array[1];
  ss << sorted_array[2];
  // Convert the string to int
  return std::strtoul(ss.str().c_str(), nullptr, 0);
}

// Generates a unique Id from the last 2 cards
int GenerateSecondUniqueId(const std::array<int, 5>& sorted_array) {
  std::stringstream ss;
  // Converts a vector of cards to a specific id of x digits.
  ss << sorted_array[3];
  ss << sorted_array[4];
  // Convert the string to int
  return std::stoi(ss.str().c_str());
}

std::array<int, 5> GenerateSortedArray(const std::array<Card, 3>& combo3,
                                       const std::array<Card, 2>& combo2) {
  std::array<int, 5> cards;
  for (std::size_t i = 0; i < 3; ++i) {
    cards[i] = CardToUniqueId(combo3[i]);
  }
  cards[3] = CardToUniqueId(combo2[0]);
  cards[4] = CardToUniqueId(combo2[1]);
  std::sort(cards.begin(), cards.end());
  return cards;
}

// Checks to see if a sorted array of 5 cards are unique
bool IsUnique(const std::array<int, 5>& sorted_cards) {
  for (std::size_t i = 0; i < 4; ++i) {
    if (sorted_cards[i] == sorted_cards[i + 1]) {
      return false;
    }
  }
  return true;
}

}  // namespace

TableGenerator::TableGenerator(const std::vector<Card>& exclusions)
    : exclusions_(exclusions) {}

std::vector<Table> TableGenerator::GenerateCombinations() {
  std::vector<Table> combinations;
  std::cout << __LINE__ << std::endl;
  std::vector<Combo3> first_three_combos = GenerateFirstThreeCombinations();

  // Generate last two combinations (ignoring the first three card combos)
  std::vector<Combo2> last_two_combos =
      GenerateLastTwoComboinations(exclusions_);

  // Need to mux these two combos into a single set that avoids duplicates
  return MuxLastTwoCombos(first_three_combos, last_two_combos);
}

std::vector<Table> TableGenerator::GenerateCombinations(Card first_card,
                                                        Card second_card,
                                                        Card third_card) {
  std::vector<Combo3> first_three_combos{
      Combo3{first_card, second_card, third_card}};
  std::vector<Card> exclusions = exclusions_;

  // Add the first three cards to the exclusions
  exclusions.push_back(first_card);
  exclusions.push_back(second_card);
  exclusions.push_back(third_card);
  // Generate last two combinations (excluding the first three card combos)
  std::vector<Combo2> last_two_combos =
      GenerateLastTwoComboinations(exclusions);
  return MuxLastTwoCombos(first_three_combos, last_two_combos);
}

std::vector<Table> TableGenerator::GenerateCombinations(Card first_card,
                                                        Card second_card,
                                                        Card third_card,
                                                        Card fourth_card) {
  std::vector<Card> exclusions = exclusions_;
  // Add the first four cards to the exclusions
  exclusions.push_back(first_card);
  exclusions.push_back(second_card);
  exclusions.push_back(third_card);
  exclusions.push_back(fourth_card);

  // Generate a list of the last cards
  DeckStackFactory deck_factory(exclusions);
  std::stack<Card> fifth_cards = deck_factory.CreateSimpleStack();

  // Mux the first four, and the last stack
  std::vector<Table> combinations;
  while (!fifth_cards.empty()) {
    const Card& fifth_card = fifth_cards.top();
    combinations.push_back(
        Table(first_card, second_card, third_card, fourth_card, fifth_card));
    fifth_cards.pop();
  }
  return combinations;
}

std::vector<Table> TableGenerator::MuxLastTwoCombos(
    const std::vector<Combo3>& first_three_combos,
    const std::vector<Combo2>& last_two_combos) {
  std::vector<Table> combinations;
  // Create a map where the key is the first three sorted cards, the value is
  // a set of the last two sorted cards gauranteed to be unique
  std::unordered_map<unsigned long, std::unordered_set<int>> map(
      first_three_combos.size());

  for (const Combo3& combo3 : first_three_combos) {
    for (const Combo2& combo2 : last_two_combos) {
      std::array<int, 5> sorted_array = GenerateSortedArray(combo3, combo2);
      if (!IsUnique(sorted_array)) {
        continue;
      }
      unsigned long first_key = GenerateFirstUniqueId(sorted_array);
      int second_key = GenerateSecondUniqueId(sorted_array);
      // Get Set
      if (map.find(first_key) == map.end()) {
        map[first_key] = std::unordered_set<int>(last_two_combos.size());
      }
      std::unordered_set<int>& set = map[first_key];

      // Check to see if second key is unique
      if (set.find(second_key) == set.end()) {
        // Indeed unique
        set.insert(second_key);
        combinations.push_back(
            Table{combo3[0], combo3[1], combo3[2], combo2[0], combo2[1]});
      }
    }
  }

  return combinations;
}

std::vector<TableGenerator::Combo2>
TableGenerator::GenerateLastTwoComboinations(
    const std::vector<Card>& exclusions) {
  std::vector<Combo2> last_two_combos;
  DeckStackFactory deck_factory(exclusions);
  std::stack<Card> first_deck = deck_factory.CreateSimpleStack();
  HandGenerator hand_generator(exclusions);
  // This generates the last two combinations, ignoring any excluded card
  std::vector<PlayerHand> hands = hand_generator.GenerateCombinations();

  // For each combo, add to the vector.
  // Each combo is gauranteed to be unique
  for (PlayerHand hand : hands) {
    last_two_combos.push_back({hand.first_card, hand.second_card});
  }
  return last_two_combos;
}

std::vector<TableGenerator::Combo3>
TableGenerator::GenerateFirstThreeCombinations() {
  std::vector<Combo3> first_three_combos;
  // Generate deck of 48 cards
  DeckStackFactory deck_factory(exclusions_);
  std::stack<Card> first_deck = deck_factory.CreateSimpleStack();
  std::vector<Card> first_exclusions = exclusions_;

  // Start with the first card
  while (!first_deck.empty()) {
    Card first_card = first_deck.top();
    first_deck.pop();

    // Generate exclusions, persist exclusions because the first card will
    // exist in every possible combination from the following two cards
    first_exclusions.push_back(first_card);

    // Generate all combos for the first and second position
    HandGenerator hand_generator(first_exclusions);
    std::vector<PlayerHand> second_third_combo =
        hand_generator.GenerateCombinations();

    // For each combo, add to the vector.
    // Each combo is gauranteed to be unique
    for (PlayerHand hand : second_third_combo) {
      Card second_card = hand.first_card;
      Card third_card = hand.second_card;
      first_three_combos.push_back({first_card, second_card, third_card});
    }
  }
  return first_three_combos;
}

}  // namespace statistics
}  // namespace poker
