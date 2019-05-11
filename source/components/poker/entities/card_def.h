#ifndef CARD_DEF_H_
#define CARD_DEF_H_

#include <iostream>
#include <vector>

namespace poker {
constexpr int kStartingId = 1;
constexpr int kEndingId = 53;

enum Suit {
  SUIT_UNKNOWN = 0,
  SUIT_SPADE,
  SUIT_CLUB,
  SUIT_DIAMOND,
  SUIT_HEART,
  SUIT_HIDDEN,
};

// These must be in congruent order as many of the code base assumes this such
// as the point calculator.
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
  CARD_VALUE_HIDDEN,
};

struct Card {
  CardValue value;
  Suit suit;
  Card();
  explicit Card(CardValue, Suit);
  Card& operator=(const Card& from);
  Card(int unique_id);
};

struct PlayerHand {
  PlayerHand() = default;
  PlayerHand(Card fc, Card sc);
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
  Table(Card first_card, Card second_card, Card third_card, Card fourth_card,
        Card fifth_card);
  TableState table_state = TABLE_STATE_RIVER;
  Card first_card;
  Card second_card;
  Card third_card;
  Card fourth_card;
  Card fifth_card;
};

int CardToUniqueId(const Card& card);
Card UniqueIdToCard(int);
int64_t CardsToUniqueId(const std::vector<Card>& cards);

std::ostream& operator<<(std::ostream& ss, Card card);
std::ostream& operator<<(std::ostream& ss, PlayerHand hand);
bool operator==(const Card& left_card, const Card& right_card);
bool operator!=(const Card& left_card, const Card& right_card);
bool operator<(const Card& left_card, const Card& right_card);

}  // namespace poker

#endif  // CARD_DEF_H_
