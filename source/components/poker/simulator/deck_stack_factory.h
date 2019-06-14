#ifndef DECK_STACK_H_
#define DECK_STACK_H_

#include <stack>
#include <vector>
#include <unordered_set>

#include "components/poker/entities/card_def.h"

namespace poker {

class DeckStackFactory {
 public:
  DeckStackFactory();
  explicit DeckStackFactory(const std::vector<Card>& exclusions);

  std::stack<Card> CreateSimpleStack() const;

 private:
  void Populate(Suit suit, std::stack<Card>* stack) const;

  bool IsExcluded(const Card& card) const;

  const std::unordered_set<int> exclusions_;
};

}  // namespace poker

#endif  // DECK_STACK_H_
