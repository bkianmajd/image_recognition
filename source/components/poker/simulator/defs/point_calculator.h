#ifndef POINT_CALCULATOR_H_
#define POINT_CALCULATOR_H_

#include <gtest/gtest_prod.h>
#include <algorithm>
#include <array>
#include <unordered_map>

#include "components/poker/entities/card_def.h"

namespace poker {
namespace simulator {

using Points = int;

class PointCalculator {
 public:
  PointCalculator(const std::vector<Card>& unsorted_cards);

  Points GetPoints();

 private:
  FRIEND_TEST(PointCalculatorTest, SortTest);
  FRIEND_TEST(PointCalculatorTest, ValueMapTest);
  FRIEND_TEST(PointCalculatorTest, RoyalFlushTest);
  FRIEND_TEST(PointCalculatorTest, FourTest);
  FRIEND_TEST(PointCalculatorTest, StraightFlushTest);
  FRIEND_TEST(PointCalculatorTest, FullHouseTest);
  FRIEND_TEST(PointCalculatorTest, FlushTest);
  FRIEND_TEST(PointCalculatorTest, StraightTest);
  FRIEND_TEST(PointCalculatorTest, ThreeTest);
  FRIEND_TEST(PointCalculatorTest, TwoTest);
  FRIEND_TEST(PointCalculatorTest, PairTest);
  FRIEND_TEST(PointCalculatorTest, HighCardTest);

  using Hand = std::array<Card, 5>;
  using Count = int;
  // MinorPoint is 2 hex value from 0 - F. F being the highest. e.g. FF
  using MinorPoint = int;

  // Called in the order below:
  MinorPoint RoyalFlush() const;
  // The next two functions updates the caches booleans
  MinorPoint FourOfAKindAndUpdate();
  MinorPoint StraightFlushAndUpdate();
  // |has_flush_| and |has_straight_| is initialized by here
  MinorPoint FullHouse() const;
  MinorPoint Flush() const;
  MinorPoint Straight() const;
  MinorPoint ThreeOfAKind() const;
  MinorPoint TwoPair() const;
  MinorPoint Pair() const;
  MinorPoint HighCard() const;

  // helper functions
  bool RoyalStraight() const;
  bool HasFlushFromStraight(CardValue begining_value) const;

  // Sorts the cards - with the exception of ace, which gets stored as the
  // largest value
  const std::vector<Card> value_sorted_cards_;
  // Counts the number of values for a particular value
  const std::unordered_map<CardValue, Count> value_map_;

  // Caching the following values for speed. It either equals kUnknown, kFalse,
  // or some value.
  MinorPoint flush_point_;
  MinorPoint straight_point_;
  MinorPoint three_of_kind_point_;
  MinorPoint pair_point_;
};

}  // namespace simulator
}  // namespace poker

#endif  // POINT_CALCULATOR_H_
