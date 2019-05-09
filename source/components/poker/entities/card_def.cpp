#include "components/poker/entities/card_def.h"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace poker {

Card::Card() {
  value = CARD_VALUE_UNKNOWN;
  suit = SUIT_UNKNOWN;
}

Card::Card(int uniqueId) { *this = UniqueIdToCard(uniqueId); }

Card::Card(CardValue arg_value, Suit arg_suit)
    : value(arg_value), suit(arg_suit) {}

PlayerHand::PlayerHand(Card fc, Card sc) : first_card(fc), second_card(sc) {}

Table::Table(Card frst_card, Card scnd_card, Card thrd_card, Card frth_card,
             Card ffth_card)
    : first_card(frst_card),
      second_card(scnd_card),
      third_card(thrd_card),
      fourth_card(frth_card),
      fifth_card(ffth_card) {}

std::ostream& operator<<(std::ostream& ss, PlayerHand hand) {
  ss << "[" << hand.first_card << "] ";
  ss << "[" << hand.second_card << "]" << std::endl;
  return ss;
}

std::ostream& operator<<(std::ostream& ss, Card card) {
  switch (card.value) {
    case 0:
      ss << "UNOWN_VALUE ";
      break;
    case 11:
      ss << "J";
      break;
    case 12:
      ss << "Q";
      break;
    case 13:
      ss << "K";
      break;
    case 14:
      ss << "HIDDEN ";
      break;
    default:
      ss << card.value;
  }

  switch (card.suit) {
    case SUIT_UNKNOWN:
      ss << "SUIT_UNKNOWN";
      break;
    case SUIT_SPADE:
      ss << "S";
      break;
    case SUIT_CLUB:
      ss << "C";
      break;
    case SUIT_DIAMOND:
      ss << "D";
      break;
    case SUIT_HEART:
      ss << "H";
      break;
    case SUIT_HIDDEN:
      ss << "HIDDEN";
      break;
  }
  return ss;
}

Card& Card::operator=(const Card& from) {
  this->suit = from.suit;
  this->value = from.value;
  return *this;
}

bool operator==(const Card& left_card, const Card& right_card) {
  return (left_card.suit == right_card.suit) &&
         (left_card.value == right_card.value);
}

bool operator!=(const Card& left_card, const Card& right_card) {
  return !(left_card == right_card);
}

bool operator<(const Card& left_card, const Card& right_card) {
  int x = CardToUniqueId(left_card);
  int y = CardToUniqueId(right_card);
  return x < y;
}

int CardToUniqueId(const Card& card) {
  // Hidden card value is 53, the suit is assumed hidden automatically
  if (card.value == CARD_VALUE_HIDDEN || card.suit == SUIT_HIDDEN) {
    return 53;
  }
  // Unkown value is 0, the suit is also assumed unknown
  return static_cast<int>(card.value) +
         (13 * (static_cast<int>(card.suit) - 1));
}

Card UniqueIdToCard(int id) {
  Card card;
  if (id == 53) {
    card.suit = SUIT_HIDDEN;
    card.value = CARD_VALUE_HIDDEN;
    return card;
  }
  if (id == 0 || id > 53) {
    card.suit = SUIT_HIDDEN;
    card.value = CARD_VALUE_HIDDEN;
    return card;
  }
  int value = id % 13;
  if (value == 0) {
    value = 13;  // Values are indexed 1
  }
  int suit = (id - value) / 13;

  card.value = static_cast<CardValue>(value);
  card.suit = static_cast<Suit>(suit + 1);
  return card;
}

int64_t CardsToUniqueId(const std::vector<Card>& cards) {
  std::vector<Card> sorted_cards(cards);
  std::sort(sorted_cards.begin(), sorted_cards.end());

  if (cards.size() > 7) {
    std::cerr << "Max is 7" << std::endl;
    assert(false);
  }

  if (sorted_cards.size() == 0) {
    return 0;
  }

  int64_t sorted_id = 0;
  for (size_t i = 0; i < sorted_cards.size(); ++i) {
    // The cards are sorted - the first card gets put into the left. e.g 01xxxx.
    // We do this by multiplying by an offset
    size_t effective_size = sorted_cards.size() - i;
    int64_t offset =
        static_cast<int64_t>(std::pow(10, 2 * (effective_size - 1)));

    sorted_id = CardToUniqueId(sorted_cards[i]) * offset + sorted_id;
  }

  return sorted_id;
}

}  // namespace poker
