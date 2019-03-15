#ifndef HAND_GENERATOR_H_
#define HAND_GENERATOR_H_

#include <vector>

#include "components/poker/entities/card_def.h"
#include "components/poker/simulator/deck_stack_factory.h"

namespace poker {
namespace statistics {

/// Generates all the hand(2 card) possibilities for a given player
class HandGenerator {
 public:
  explicit HandGenerator(const std::vector<Card>& exclusions);

  std::vector<PlayerHand> GenerateCombinations();

 private:
  void AddCombinationSet(std::stack<Card>* deck);

  const DeckStackFactory deck_factory_;

  std::vector<PlayerHand> combinations_;
};

}  // namespace statistics
}  // namespace poker

#endif  // HAND_GENERATOR_H_
