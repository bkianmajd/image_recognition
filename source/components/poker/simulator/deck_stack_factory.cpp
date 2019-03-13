#include "components/poker/simulator/deck_stack_factory.h"

#include <stack>
#include <vector>

#include "components/poker/entities/card_def.h"

namespace poker {
namespace {
std::unordered_set<int> PopulateExclusions(
    const std::vector<Card>& exclusions) {
  std::unordered_set<int> set;

  for (Card excluded_card : exclusions) {
    set.insert(CardToUniqueId(excluded_card));
  }
  return set;
}
}  // namespace

DeckStackFactory::DeckStackFactory(const std::vector<Card>& exclusions)
    : exclusions_(PopulateExclusions(exclusions)) {}

DeckStackFactory::DeckStackFactory() {}

std::stack<Card> DeckStackFactory::CreateSimpleStack() const {
  std::stack<Card> stack;
  for (int i = kStartingId; i < kEndingId; ++i) {
    Card card = UniqueIdToCard(i);
    if (!IsExcluded(card)) {
      stack.push(card);
    }
  }
  return stack;
}

bool DeckStackFactory::IsExcluded(Card card) const {
  int id = CardToUniqueId(card);
  auto it = exclusions_.find(id);
  // if the iterator exists, it is exclused
  return (it != exclusions_.end());
}

}  // namespace poker
