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
  Populate(SUIT_SPADE, &stack);
  Populate(SUIT_CLUB, &stack);
  Populate(SUIT_DIAMOND, &stack);
  Populate(SUIT_HEART, &stack);

  return stack;
}

void DeckStackFactory::Populate(Suit suit, std::stack<Card>* stack) const {
  const Card kCard1{CARD_VALUE_ACE, suit};
  const Card kCard2{CARD_VALUE_TWO, suit};
  const Card kCard3{CARD_VALUE_THREE, suit};
  const Card kCard4{CARD_VALUE_FOUR, suit};
  const Card kCard5{CARD_VALUE_FIVE, suit};
  const Card kCard6{CARD_VALUE_SIX, suit};
  const Card kCard7{CARD_VALUE_SEVEN, suit};
  const Card kCard8{CARD_VALUE_EIGHT, suit};
  const Card kCard9{CARD_VALUE_NINE, suit};
  const Card kCard10{CARD_VALUE_TEN, suit};
  const Card kCard11{CARD_VALUE_JACK, suit};
  const Card kCard12{CARD_VALUE_QUEEN, suit};
  const Card kCard13{CARD_VALUE_KING, suit};
  if (!IsExcluded(kCard1)) {
    stack->push(kCard1);
  }
  if (!IsExcluded(kCard2)) {
    stack->push(kCard2);
  }
  if (!IsExcluded(kCard3)) {
    stack->push(kCard3);
  }
  if (!IsExcluded(kCard4)) {
    stack->push(kCard4);
  }
  if (!IsExcluded(kCard5)) {
    stack->push(kCard5);
  }
  if (!IsExcluded(kCard6)) {
    stack->push(kCard6);
  }
  if (!IsExcluded(kCard7)) {
    stack->push(kCard7);
  }
  if (!IsExcluded(kCard8)) {
    stack->push(kCard8);
  }
  if (!IsExcluded(kCard9)) {
    stack->push(kCard9);
  }
  if (!IsExcluded(kCard10)) {
    stack->push(kCard10);
  }
  if (!IsExcluded(kCard11)) {
    stack->push(kCard11);
  }
  if (!IsExcluded(kCard12)) {
    stack->push(kCard12);
  }
  if (!IsExcluded(kCard13)) {
    stack->push(kCard13);
  }
}

bool DeckStackFactory::IsExcluded(const Card& card) const {
  int id = CardToUniqueId(card);
  auto it = exclusions_.find(id);
  // if the iterator exists, it is exclused
  return (it != exclusions_.end());
}

}  // namespace poker
