#include "components/poker/entities/card_def.h"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace poker {
namespace {

template <typename ArrayType>
CardsId CardsToUniqueId(const ArrayType& cards) {
  ArrayType sorted_cards(cards);
  // Sort the cards, from smallest to largest (i.e. 2 3 4 5)
  std::sort(sorted_cards.begin(), sorted_cards.end());

  // The shift offset moves each CardId by one hex digit
  int shift_offset = 0;

  // Each individual cards unique id is stored and aggregated into the CardsId
  CardsId cards_id = 0;
  // The largest card is the most significant bit
  for (size_t i = 0; i < cards.size(); ++i) {
    CardsId shift = CardToUniqueId(sorted_cards[static_cast<size_t>(i)]);
    // The proceeding cards are shifted more
    shift = shift << shift_offset;
    cards_id = cards_id + shift;
    shift_offset = shift_offset + 8;
  }
  return cards_id;
}

}  // namespace

std::ostream& operator<<(std::ostream& ss, PlayerHand player_hand) {
  ss << "left: " << player_hand.FirstCard() << " "
     << "right: " << player_hand.SecondCard() << std::endl;
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

// ==========Card===============
Card::Card() {
  value = CARD_VALUE_UNKNOWN;
  suit = SUIT_UNKNOWN;
}

Card::Card(CardId uniqueId) { *this = UniqueIdToCard(uniqueId); }

Card::Card(CardValue arg_value, Suit arg_suit)
    : value(arg_value), suit(arg_suit) {}

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

CardId Card::UniqueId() const { return CardToUniqueId(*this); }

// End ==========Card===============

// ==========PlayerHand===============
PlayerHand::PlayerHand(const Card& fc, const Card& sc) : cards_({{fc, sc}}) {}

PlayerHand::PlayerHand(CardsId id)
    : cards_{
          {UniqueIdToCard(id & 0x00FF), UniqueIdToCard((id & 0xFF00) >> 8)}} {}

Card& PlayerHand::FirstCard() { return cards_[0]; }
Card& PlayerHand::SecondCard() { return cards_[1]; }
const Card& PlayerHand::FirstCard() const { return cards_[0]; }
const Card& PlayerHand::SecondCard() const { return cards_[1]; }

CardsId PlayerHand::UniqueId() const { return CardsToUniqueId(cards_); }

std::ostream& operator<<(std::ostream& ss, const PlayerHand& hand) {
  ss << "[" << hand.FirstCard() << "] ";
  ss << "[" << hand.SecondCard() << "]" << std::endl;
  return ss;
}

// End ==========PlayerHand===============

// ==========Table===============
Table::Table() {}
Table::Table(Card frst_card, Card scnd_card, Card thrd_card, Card frth_card,
             Card ffth_card)
    : cards_{{frst_card, scnd_card, thrd_card, frth_card, ffth_card}} {}
Table::Table(CardsId id)
    : cards_(
          {{UniqueIdToCard(id & 0x0000FF), UniqueIdToCard((id & 0x00FF00) >> 8),
            UniqueIdToCard((id & 0xFF0000) >> 16),
            UniqueIdToCard((id & 0xFF000000) >> 24),
            UniqueIdToCard((id & 0xFF00000000) >> 32)}}) {}

CardsId Table::UniqueId() const { return CardsToUniqueId(cards_); }

// End ==========Table===============

// ==========CardCombo===============
CardCombo::CardCombo(const PlayerHand& player_hand)
    : cards_({{player_hand.FirstCard(), player_hand.SecondCard(), 0, 0, 0, 0,
               0}}) {}
CardCombo::CardCombo(const Table& table)
    : cards_({{0, 0, table.cards_[0], table.cards_[1], table.cards_[2],
               table.cards_[3], table.cards_[4]}}) {}
CardCombo::CardCombo(const PlayerHand& player_hand, const Table& table)
    : cards_({{player_hand.FirstCard(), player_hand.SecondCard(),
               table.cards_[0], table.cards_[1], table.cards_[2],
               table.cards_[3], table.cards_[4]}}) {}
CardCombo::CardCombo(CardsId id)
    : cards_(
          {{UniqueIdToCard(id & 0x0000FF), UniqueIdToCard((id & 0x00FF00) >> 8),
            UniqueIdToCard((id & 0xFF0000) >> 16),
            UniqueIdToCard((id & 0xFF000000) >> 24),
            UniqueIdToCard((id & 0xFF00000000) >> 32),
            UniqueIdToCard((id & 0xFF0000000000) >> 40),
            UniqueIdToCard((id & 0xFF000000000000) >> 48)}}) {}
CardCombo::CardCombo(CardId hand_id, CardId table_id)
    : CardCombo(PlayerHand(hand_id), Table(table_id)) {}

CardsId CardCombo::UniqueId() { return CardsToUniqueId(cards_); }
// End ==========CardCombo===============

// ========== Static functions =============
Card UniqueIdToCard(CardId id) {
  Card card;
  // Shift by one hex value
  switch (id & 0X0F) {
    case 0x02:
      card.suit = SUIT_SPADE;
      break;
    case 0x03:
      card.suit = SUIT_CLUB;
      break;
    case 0x04:
      card.suit = SUIT_DIAMOND;
      break;
    case 0x05:
      card.suit = SUIT_HEART;
      break;
    case 0x0F:
      card.suit = SUIT_HIDDEN;
      break;
    default:
      card.suit = SUIT_UNKNOWN;
  }

  switch (id & 0XF0) {
    case 0x20:
      card.value = CARD_VALUE_TWO;
      break;
    case 0x30:
      card.value = CARD_VALUE_THREE;
      break;
    case 0x40:
      card.value = CARD_VALUE_FOUR;
      break;
    case 0x50:
      card.value = CARD_VALUE_FIVE;
      break;
    case 0x60:
      card.value = CARD_VALUE_SIX;
      break;
    case 0x70:
      card.value = CARD_VALUE_SEVEN;
      break;
    case 0x80:
      card.value = CARD_VALUE_EIGHT;
      break;
    case 0x90:
      card.value = CARD_VALUE_NINE;
      break;
    case 0xA0:
      card.value = CARD_VALUE_TEN;
      break;
    case 0xB0:
      card.value = CARD_VALUE_JACK;
      break;
    case 0xC0:
      card.value = CARD_VALUE_QUEEN;
      break;
    case 0xD0:
      card.value = CARD_VALUE_KING;
      break;
    case 0xE0:
      card.value = CARD_VALUE_ACE;
      break;
    case 0xF0:
      card.value = CARD_VALUE_HIDDEN;
      break;
    default:
      card.value = CARD_VALUE_UNKNOWN;
  }
  return card;
}

CardId CardToUniqueId(const Card& card) {
  CardId unique_id;
  switch (card.value) {
    case CARD_VALUE_ACE:
      unique_id = 0x0E;
      break;
    case CARD_VALUE_TWO:
      unique_id = 0x02;
      break;
    case CARD_VALUE_THREE:
      unique_id = 0x03;
      break;
    case CARD_VALUE_FOUR:
      unique_id = 0x04;
      break;
    case CARD_VALUE_FIVE:
      unique_id = 0x05;
      break;
    case CARD_VALUE_SIX:
      unique_id = 0x06;
      break;
    case CARD_VALUE_SEVEN:
      unique_id = 0x07;
      break;
    case CARD_VALUE_EIGHT:
      unique_id = 0x08;
      break;
    case CARD_VALUE_NINE:
      unique_id = 0x09;
      break;
    case CARD_VALUE_TEN:
      unique_id = 0x0A;
      break;
    case CARD_VALUE_JACK:
      unique_id = 0x0B;
      break;
    case CARD_VALUE_QUEEN:
      unique_id = 0x0C;
      break;
    case CARD_VALUE_KING:
      unique_id = 0x0D;
      break;
    case CARD_VALUE_HIDDEN:
      unique_id = 0x0F;
      break;
    default:
      unique_id = 0x0;
  }
  // Shift by one hex value
  unique_id = static_cast<CardId>(unique_id << 4);
  switch (card.suit) {
    case SUIT_HIDDEN:
      unique_id = unique_id + 0x0F;
      break;
    case SUIT_SPADE:
      unique_id = unique_id + 0x02;
      break;
    case SUIT_CLUB:
      unique_id = unique_id + 0x03;
      break;
    case SUIT_DIAMOND:
      unique_id = unique_id + 0x04;
      break;
    case SUIT_HEART:
      unique_id = unique_id + 0x05;
      break;
    default:
      unique_id = 0;
  }
  return unique_id;
}

}  // namespace poker
