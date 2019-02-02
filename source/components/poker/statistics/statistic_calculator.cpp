#include "components/poker/statistics/statistic_calculator.h"

namespace poker {
namespace {
constexpr int kDeckSize = 52;
// There are 13 suits
constexpr int kSuitSize = 13;
// There are 4 values
constexpr int kValueSize = 4;

}  // namespace

StatisticCalculator::StatisticCalculator()
    : cards_remaining_(50), turns_left_(0) {}

void StatisticCalculator::UpdateGameModel(const GameModel& game_model) {
  // Reset members
  turns_left_ = 0;
  active_cards_.clear();
  suit_counter_.clear();
  value_counter_.clear();

  // Store all player hands into set
  for (size_t i = 0; i < game_model.player_hands.size(); ++i) {
    const PlayerHand& player_hand = game_model.player_hands[i];
    AddCardToSet(player_hand.first_card);
    AddCardToSet(player_hand.second_card);
  }
  // Add all dealer cards to set
  for (size_t i = DEALER_ONE; i < DEALER_MAX_SIZE; ++i) {
    const Card& dealer_hand = game_model.dealer_cards[i];
    AddCardToSet(dealer_hand);
  }
  // Count turns left by the cards the dealer has yet to deal
  for (size_t i = DEALER_ONE; i < DEALER_MAX_SIZE; ++i) {
    const Card& dealer_hand = game_model.dealer_cards[i];
    if (dealer_hand.value == CARD_VALUE_UNKNOWN) {
      turns_left_++;
    }
  }
}

double StatisticCalculator::CalculateProbability(Card card) {
  int id = CardToUniqueId(card);
  // The card is already here! Technically should not be called
  if (active_cards_.find(id) != active_cards_.end()) {
    return 0;
  }
  // Probability is 1 / cards_remaining
  return 1 / cards_remaining_;
}

double StatisticCalculator::CalculateProbability(Suit suit) {
  // First find how many suits are remaining
  int suit_remaining = kSuitSize - suit_counter_[suit];

  assert(suit_remaining > -1);
  // Probability is suit_remaining / cards_remaining
  return suit_remaining / cards_remaining_;
}

double StatisticCalculator::CalculateProbability(CardValue value) {
  // First find how many of the same number are remaining
  int value_remaining = kValueSize - value_counter_[value];
  assert(value_remaining > -1);

  // Probability is value_remaining / cards_remaining
  return value_remaining / cards_remaining_;
}

double StatisticCalculator::CalculateProbabilityAtLeastOnce(CardValue value) {
  // First find how many of the same number are remaining
  int value_remaining = kValueSize - value_counter_[value];
  assert(value_remaining > -1);
  assert(cards_remaining_ > turns_left_);

  // The probability is equal to 1 - the probability the value never appears
  double p = 1;
  int cards_remaining = cards_remaining_;
  for (int i = 0; i < turns_left_; ++i) {
    p = p * value_remaining / cards_remaining;
    cards_remaining--;
  }
  return 1 - p;
}

double StatisticCalculator::CalculateProbabilityAtLeastOnce(Card card) {
  int id = CardToUniqueId(card);
  // The card is already here! Technically should not be called
  if (active_cards_.find(id) != active_cards_.end()) {
    return 0;
  }

  // Cards remaining should always be greater than turns left
  assert(cards_remaining_ > turns_left_);

  // The probability is equal to 1 - the probability the card never appears
  double p = 1;
  int cards_remaining = cards_remaining_;
  for (int i = 0; i < turns_left_; ++i) {
    p = p * (cards_remaining - 1) / cards_remaining;
    cards_remaining--;
  }
  return 1 - p;
}

double StatisticCalculator::CalculateProbabilityAtLeastOnce(Suit suit) {
  // First find how many suits are remaining
  int suit_remaining = kSuitSize - suit_counter_[suit];

  assert(cards_remaining_ > turns_left_);
  // The probability is equal to 1 - the probability the suit never appears
  double p = 1;
  int cards_remaining = cards_remaining_;
  for (int i = 0; i < turns_left_; ++i) {
    p = p * suit_remaining / cards_remaining;
    cards_remaining--;
  }
  return 1 - p;
}

void StatisticCalculator::AddCardToSet(const Card& card) {
  // ignore if card is hidden or unknown because the caller is expecting a 52
  // card deck
  if (card.value == CARD_VALUE_UNKNOWN) {
    return;
  }
  if (card.value == CARD_VALUE_HIDDEN) {
    return;
  }

  active_cards_.insert(CardToUniqueId(card));
  cards_remaining_ = kDeckSize - static_cast<int>(active_cards_.size());

  // Add the suit
  if (suit_counter_.find(card.suit) == suit_counter_.end()) {
    suit_counter_[card.suit] = 1;
  } else {
    int counter = suit_counter_[card.suit];
    suit_counter_[card.suit] = counter + 1;
  }

  // Add the value counter
  if (value_counter_.find(card.value) == value_counter_.end()) {
    value_counter_[card.value] = 1;
  } else {
    int counter = value_counter_[card.value];
    value_counter_[card.value] = counter + 1;
  }
}

}  // namespace poker
