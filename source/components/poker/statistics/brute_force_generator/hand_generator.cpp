#include "components/poker/statistics/brute_force_generator/hand_generator.h"

namespace poker {
namespace statistics {
// HandGenerator::HandGenerator() {}

}  // namespace statistics
}  // namespace poker

#include <vector>

namespace poker {
namespace statistics {

HandGenerator::HandGenerator(const std::vector<Card>& exclusions)
    : deck_factory_(exclusions), deck_(deck_factory_.CreateSimpleStack()) {}

std::vector<PlayerHand> HandGenerator::GenerateCombinations() {
  while (!deck_.empty()) {
    AddCombinationSet();
  }
  return combinations_;
}

void HandGenerator::AddCombinationSet() {
  std::stack<Card> temp_stack;

  // Get first card
  Card first_card = deck_.top();
  deck_.pop();

  // Try every combination with the first card
  while (!deck_.empty()) {
    combinations_.push_back(PlayerHand(first_card, deck_.top()));
    temp_stack.push(deck_.top());
    deck_.pop();
  }

  // Now increment through the next stack, omit the first card from stack
  // because each combination has been exhausted
  std::swap(temp_stack, deck_);
}

}  // namespace statistics
}  // namespace poker
