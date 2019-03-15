#ifndef TABLE_GENERATOR_H_
#define TABLE_GENERATOR_H_

#include <array>
#include <vector>

#include "components/poker/entities/card_def.h"
#include "components/poker/simulator/deck_stack_factory.h"
#include "components/poker/statistics/brute_force_generator/hand_generator.h"

namespace poker {
namespace statistics {

/// Generates all the card possibilities on a table for a given pair of hands,
/// and oponents hands
class TableGenerator {
 public:
  explicit TableGenerator(const std::vector<Card>& exclusions);
  std::vector<Table> GenerateCombinations();

  std::vector<Table> GenerateCombinations(Card first_card, Card second_card,
                                          Card third_card);

  std::vector<Table> GenerateCombinations(Card first_card, Card second_card,
                                          Card third_card, Card fourth_card);

 private:
  using Combo2 = std::array<Card, 2>;
  using Combo3 = std::array<Card, 3>;
  std::vector<Table> MuxLastTwoCombos(
      const std::vector<Combo3>& first_three_combos,
      const std::vector<Combo2>& last_two_combos);

  std::vector<Combo2> GenerateLastTwoComboinations(
      const std::vector<Card>& exclusions);

  // These are gauranteed to be unique
  std::vector<Combo3> GenerateFirstThreeCombinations();

  const std::vector<Card> exclusions_;
};

}  // namespace statistics
}  // namespace poker

#endif  // TABLE_GENERATOR_H_
