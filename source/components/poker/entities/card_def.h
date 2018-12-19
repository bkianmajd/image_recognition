#ifndef CARD_DEF_H_
#define CARD_DEF_H_

namespace poker {

enum Suit {
  SUIT_UNKNOWN = 0,
  SUIT_SPADE,
  SUIT_CLUB,
  SUIT_DIAMOND,
  SUIT_HEART,
};

enum CardValue {
  CARD_VALUE_UNKNOWN = 0,
  CARD_VALUE_ACE = 1,
  CARD_VALUE_TWO = 2,
  CARD_VALUE_THREE = 3,
  CARD_VALUE_FOUR = 4,
  CARD_VALUE_FIVE = 5,
  CARD_VALUE_SIX = 6,
  CARD_VALUE_SEVEN = 7,
  CARD_VALUE_EIGHT = 8,
  CARD_VALUE_NINE = 9,
  CARD_VALUE_TEN = 10,
  CARD_VALUE_JACK = 11,
  CARD_VALUE_QUEEN = 12,
  CARD_VALUE_KING = 13,
};

struct Card {
  CardValue card_value = CARD_VALUE_UNKNOWN;
  Suit suit = SUIT_UNKNOWN;
};

struct PlayerHand {
  bool in_hand = false;
  Card first_card;
  Card second_card;
};

enum TableState {
  TABLE_STATE_PRE_FLOP = 0,
  TABLE_STATE_FLOP,
  TABLE_STATE_TURN,
  TABLE_STATE_RIVER,
};

struct Table {
  TableState table_state = TABLE_STATE_PRE_FLOP;
  Card first_card;
  Card second_card;
  Card third_card;
  Card fourth_card;
  Card fifth_card;
};

}  // namespace poker

#endif  // CARD_DEF_H_
