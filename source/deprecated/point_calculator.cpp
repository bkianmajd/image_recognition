#include "components/poker/simulator/defs/point_calculator.h"

#include <cassert>

namespace poker {
namespace simulator {
namespace {

// returns an integer with a value or kFalse;
constexpr int kFalse = -1;
constexpr int kAce = CARD_VALUE_KING + 1;

std::vector<Card> SortCardsByValue(const std::vector<Card>& unsorted_cards) {
  std::vector<Card> retVec(unsorted_cards);

  // Sorts smallest to largest, exception is ace - which gets stored as the
  // smallest value
  std::sort(retVec.begin(), retVec.end(), [](const Card& lhs, const Card& rhs) {
    return lhs.value < rhs.value;
  });
  return retVec;
}

inline int ThreeOfAKind(const Hand& hand) {
  int count = 0;
  for(size_t i = 1; i < 5; ++i) {
    if(hand[0] == hand[i]) {
      count++;
    }
  }


}

inline int RoyalStraight(const Hand& hand) {
  if ((hand[1].value == CARD_VALUE_JACK) &&
      (hand[2].value == CARD_VALUE_QUEEN) &&
      (hand[3].value == CARD_VALUE_KING) && (hand[0].value == CARD_VALUE_ACE)) {
    return kAce;
  }
  return kFalse;
}

// returns the highest value if there is a straight
inline int Straight(const Hand& hand) {
  // Check for royal straight - otherwise ace is assumed small
  int royalStraight = RoyalStraight(hand);
  if (royalStraight != kFalse) {
    return royalStraight;
  }

  if ((hand[0].value == hand[1].value + 1) &&
      (hand[0].value == hand[2].value + 2) &&
      (hand[0].value == hand[3].value + 3) &&
      (hand[0].value == hand[4].value + 4)) {
    return hand[4].value;
  }
  return kFalse;
}

// returns the highest value if there is a flush
inline int Flush(const Hand& hand) {
  if ((hand[0].suit == hand[1].suit) && (hand[0].suit == hand[2].suit) &&
      (hand[0].suit == hand[3].suit) && (hand[0].suit == hand[4].suit)) {
    return hand[0].value == CARD_VALUE_ACE ? kAce : hand[4].value;
  }
  return kFalse;
}

inline std::pair<int, int> FullHouse(const Hand& hand) {
  // Check for three of a kind - then check if the last 2 is a pair
}

inline int FourOfKind(const Hand& hand) {
  // Check for three of a kind - then check if that value is there 4 times

  return kFalse;
}

inline bool StraightFlush(const Hand& hand) {
  // check for straight & flush
}

inline bool RoyalFlush(const Hand& hand) {
  // Check for straight flush
  // Check that first card is 10
}

}  // namespace

PointCalculator::PointCalculator(const std::vector<Card>& unsorted_cards)
    : value_sorted_cards_(SortCardsByValue(unsorted_cards)) {
  // The caller should not pass hidden or unknown cards
  for (size_t i = 0; i < unsorted_cards.size(); ++i) {
    assert(unsorted_cards[i].value != CARD_VALUE_UNKNOWN);
    assert(unsorted_cards[i].value != CARD_VALUE_HIDDEN);
    assert(unsorted_cards[i].suit != SUIT_UNKNOWN);
    assert(unsorted_cards[i].suit != SUIT_HIDDEN);
  }
}

Points PointCalculator::GetPointsFrom5(const Hand& hand) {
  // Caller needs to call with sorted array
  Points points = 0;

  return points;
}

Points PointCalculator::GetMaximumPointsFrom7() {
  const std::vector<Card>& cards = value_sorted_cards_;
  Points max_points = 0;
  // combo 1 = 0 1 2 3 4 - -
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[1], cards[2], cards[3], cards[4]}));
  // combo 2 = 0 1 2 3 - - 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[1], cards[2], cards[3], cards[6]}));
  // combo 3 = 0 1 2 - 4 - 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[1], cards[2], cards[4], cards[6]}));
  // combo 4 = 0 1 - 3 4 - 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[1], cards[3], cards[4], cards[6]}));
  // combo 5 = 0 - 2 3 4 - 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[2], cards[3], cards[4], cards[6]}));
  // combo 6 = - 1 2 3 4 - 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[1], cards[2], cards[3], cards[4], cards[6]}));
  // combo 7 = 0 1 2 3 - 5 -
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[1], cards[2], cards[3], cards[5]}));
  // combo 8 = 0 1 2 - 4 5 -
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[1], cards[2], cards[4], cards[5]}));
  // combo 9 = 0 1 - 3 4 5 -
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[1], cards[3], cards[4], cards[5]}));
  // combo 10 = 0 - 2 3 4 5 -
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[2], cards[3], cards[4], cards[5]}));
  // combo 11 = - 1 2 3 4 5 -
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[1], cards[2], cards[3], cards[4], cards[5]}));
  // combo 12 = 0 1 2 - - 5 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[1], cards[2], cards[5], cards[6]}));
  // combo 13 = 0 1 - - 4 5 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[1], cards[4], cards[5], cards[6]}));
  // combo 14 = 0 - 2 - 4 5 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[2], cards[4], cards[5], cards[6]}));
  // combo 15 = - 1 2 - 4 5 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[1], cards[2], cards[3], cards[6]}));
  // combo 16 = 0 1 - 3 - 5 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[1], cards[3], cards[5], cards[6]}));
  // combo 17 = 0 - 2 3 - 5 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[2], cards[3], cards[5], cards[6]}));
  // combo 18 = - 1 2 3 - 5 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[1], cards[2], cards[3], cards[5], cards[6]}));
  // combo 19 = 0 - - 3 4 5 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[0], cards[1], cards[2], cards[3], cards[6]}));
  // combo 20 = - - 2 3 4 5 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[2], cards[3], cards[4], cards[5], cards[6]}));
  // combo 21 = - 1 - 3 4 5 6
  max_points = std::max(
      max_points,
      GetPointsFrom5({cards[1], cards[3], cards[4], cards[5], cards[6]}));
  return max_points;
}

}  // namespace simulator
}  // namespace poker
