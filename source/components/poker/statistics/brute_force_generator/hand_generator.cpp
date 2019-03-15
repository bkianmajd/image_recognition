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
    : deck_factory_(exclusions) {}

std::vector<PlayerHand> HandGenerator::GenerateCombinations() {
  if (!combinations_.empty()) {
    return combinations_;
  }

  std::stack<Card> deck = deck_factory_.CreateSimpleStack();
  while (!deck.empty()) {
    AddCombinationSet(&deck);
  }
  return combinations_;
}

void HandGenerator::AddCombinationSet(std::stack<Card>* deck) {
  std::stack<Card> temp_stack;

  // Get first card
  Card first_card = deck->top();
  deck->pop();

  // Try every combination with the first card
  while (!deck->empty()) {
    combinations_.push_back(PlayerHand(first_card, deck->top()));
    temp_stack.push(deck->top());
    deck->pop();
  }

  // Now increment through the next stack, omit the first card from stack
  // because each combination has been exhausted
  std::swap(temp_stack, *deck);
}

}  // namespace statistics
}  // namespace poker
