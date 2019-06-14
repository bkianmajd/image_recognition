#ifndef CARD_DEF_H_
#define CARD_DEF_H_

#include <array>
#include <iostream>
#include <vector>

namespace poker {

enum Suit {
  SUIT_UNKNOWN = 0,
  SUIT_SPADE,
  SUIT_CLUB,
  SUIT_DIAMOND,
  SUIT_HEART,
  SUIT_HIDDEN,
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
  CARD_VALUE_HIDDEN,
};

// Both id's are sorted
using CardId = unsigned char;
using CardsId = uint64_t;

struct Card {
  CardValue value;
  Suit suit;
  Card();
  Card(CardValue, Suit);
  Card(CardId unique_id);
  Card& operator=(const Card& from);

  CardId UniqueId() const;
};

struct PlayerHand {
  PlayerHand() = default;
  PlayerHand(const Card& fc, const Card& sc);
  PlayerHand(CardsId id);
  Card& FirstCard();
  Card& SecondCard();
  const Card& FirstCard() const;
  const Card& SecondCard() const;

  CardsId UniqueId() const;
  std::array<Card, 2> cards_{};
};

struct Table {
  Table();
  Table(Card first_card, Card second_card, Card third_card, Card fourth_card,
        Card fifth_card);
  Table(CardsId id);

  CardsId UniqueId() const;
  std::array<Card, 5> cards_{};
};

struct CardCombo {
  CardCombo() = default;
  CardCombo(const PlayerHand& player_hand);
  CardCombo(const Table& table);
  CardCombo(const PlayerHand& player_hand, const Table& table);
  CardCombo(CardsId id);
  CardCombo(CardId hand_id, CardId table_id);

  CardsId UniqueId();
  std::array<Card, 7> cards_{};
};

Card UniqueIdToCard(CardId card_id);
CardId CardToUniqueId(const Card& card);

std::ostream& operator<<(std::ostream& ss, Card card);
std::ostream& operator<<(std::ostream& ss, const PlayerHand& hand);
bool operator==(const Card& left_card, const Card& right_card);
bool operator!=(const Card& left_card, const Card& right_card);
bool operator<(const Card& left_card, const Card& right_card);

}  // namespace poker

#endif  // CARD_DEF_H_
