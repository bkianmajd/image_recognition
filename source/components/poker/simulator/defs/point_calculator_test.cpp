#include "components/poker/simulator/defs/point_calculator.h"

#include <iostream>

#include "gtest/gtest.h"

namespace poker {
namespace simulator {
namespace {

// coppied and pasted constants from point_calculator
constexpr int kFalse = -2;
constexpr int kUnknown = 0;

}  // namespace

class PointCalculatorTest : public testing::Test {
 public:
  PointCalculatorTest() {}

 protected:
  std::vector<Card> unsorted_cards;
};

TEST_F(PointCalculatorTest, ConstructDestruct) {
  unsorted_cards.push_back(Card(14));
  unsorted_cards.push_back(Card(11));
  unsorted_cards.push_back(Card(9));
  unsorted_cards.push_back(Card(7));
  unsorted_cards.push_back(Card(4));
  unsorted_cards.push_back(Card(2));
  PointCalculator pointCalculator(unsorted_cards);
}

TEST_F(PointCalculatorTest, SortTest) {
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_TWO, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_THREE, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_KING, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_TEN, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_HEART));
  PointCalculator pointCalculator(unsorted_cards);

  EXPECT_EQ(unsorted_cards.size(), pointCalculator.value_sorted_cards_.size());

  EXPECT_EQ(CARD_VALUE_TWO, pointCalculator.value_sorted_cards_[0].value);
  EXPECT_EQ(CARD_VALUE_THREE, pointCalculator.value_sorted_cards_[1].value);
  EXPECT_EQ(CARD_VALUE_TEN, pointCalculator.value_sorted_cards_[2].value);
  EXPECT_EQ(CARD_VALUE_KING, pointCalculator.value_sorted_cards_[3].value);
  EXPECT_EQ(CARD_VALUE_ACE, pointCalculator.value_sorted_cards_[4].value);
  EXPECT_EQ(CARD_VALUE_ACE, pointCalculator.value_sorted_cards_[5].value);
}

TEST_F(PointCalculatorTest, ValueMapTest) {
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_TWO, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_THREE, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_THREE, SUIT_SPADE));
  unsorted_cards.push_back(Card(CARD_VALUE_THREE, SUIT_HEART));
  unsorted_cards.push_back(Card(CARD_VALUE_TEN, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_HEART));
  PointCalculator pointCalculator(unsorted_cards);

  EXPECT_EQ(2, pointCalculator.value_map_.at(CARD_VALUE_ACE));
  EXPECT_EQ(1, pointCalculator.value_map_.at(CARD_VALUE_TWO));
  EXPECT_EQ(3, pointCalculator.value_map_.at(CARD_VALUE_THREE));
  EXPECT_EQ(1, pointCalculator.value_map_.at(CARD_VALUE_TEN));
}

TEST_F(PointCalculatorTest, RoyalFlushTest) {
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_JACK, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_QUEEN, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_KING, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_THREE, SUIT_HEART));
  unsorted_cards.push_back(Card(CARD_VALUE_TEN, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_HEART));
  PointCalculator pointCalculator(unsorted_cards);
  EXPECT_NE(kUnknown, pointCalculator.RoyalFlush());
  EXPECT_NE(kFalse, pointCalculator.RoyalFlush());
  EXPECT_GT(pointCalculator.RoyalFlush(), 0);

  unsorted_cards.clear();
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_JACK, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_QUEEN, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_KING, SUIT_SPADE));
  unsorted_cards.push_back(Card(CARD_VALUE_THREE, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_TEN, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_SPADE));
  PointCalculator pointCalculator2(unsorted_cards);
  EXPECT_EQ(kFalse, pointCalculator2.RoyalFlush());
}

TEST_F(PointCalculatorTest, FourTest) {
  unsorted_cards.push_back(Card(CARD_VALUE_JACK, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_JACK, SUIT_HEART));
  unsorted_cards.push_back(Card(CARD_VALUE_JACK, SUIT_SPADE));
  unsorted_cards.push_back(Card(CARD_VALUE_KING, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_THREE, SUIT_HEART));
  unsorted_cards.push_back(Card(CARD_VALUE_JACK, SUIT_DIAMOND));
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_HEART));
  PointCalculator pointCalculator(unsorted_cards);
  PointCalculator::MinorPoint minor_point =
      pointCalculator.FourOfAKindAndUpdate();
  EXPECT_NE(kUnknown, minor_point);
  EXPECT_NE(kFalse, minor_point);
  EXPECT_GT(minor_point, 0);

  unsorted_cards.clear();
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_JACK, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_QUEEN, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_KING, SUIT_SPADE));
  unsorted_cards.push_back(Card(CARD_VALUE_THREE, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_TEN, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_SPADE));
  PointCalculator pointCalculator2(unsorted_cards);
  EXPECT_EQ(kFalse, pointCalculator2.FourOfAKindAndUpdate());
}

TEST_F(PointCalculatorTest, StraightFlushTest) {
  {
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_TWO, SUIT_HEART));
  unsorted_cards.push_back(Card(CARD_VALUE_THREE, SUIT_HEART));
  unsorted_cards.push_back(Card(CARD_VALUE_KING, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_FOUR, SUIT_HEART));
  unsorted_cards.push_back(Card(CARD_VALUE_FIVE, SUIT_HEART));
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_HEART));
  PointCalculator pointCalculator(unsorted_cards);
  PointCalculator::MinorPoint minor_point =
      pointCalculator.StraightFlushAndUpdate();
  EXPECT_NE(kUnknown, minor_point);
  EXPECT_GT(minor_point, 0);
  }

  {
  unsorted_cards.clear();
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_TWO, SUIT_HEART));
  unsorted_cards.push_back(Card(CARD_VALUE_THREE, SUIT_HEART));
  unsorted_cards.push_back(Card(CARD_VALUE_KING, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_FOUR, SUIT_CLUB));
  unsorted_cards.push_back(Card(CARD_VALUE_FIVE, SUIT_HEART));
  unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_HEART));
  PointCalculator pointCalculator2(unsorted_cards);
  EXPECT_EQ(kFalse, pointCalculator2.StraightFlushAndUpdate());
  }

  {
    unsorted_cards.push_back(Card(CARD_VALUE_NINE, SUIT_HEART));
    unsorted_cards.push_back(Card(CARD_VALUE_TEN, SUIT_HEART));
    unsorted_cards.push_back(Card(CARD_VALUE_JACK, SUIT_HEART));
    unsorted_cards.push_back(Card(CARD_VALUE_KING, SUIT_CLUB));
    unsorted_cards.push_back(Card(CARD_VALUE_QUEEN, SUIT_HEART));
    unsorted_cards.push_back(Card(CARD_VALUE_ACE, SUIT_HEART));
    unsorted_cards.push_back(Card(CARD_VALUE_EIGHT, SUIT_HEART));
    PointCalculator pointCalculator(unsorted_cards);
    PointCalculator::MinorPoint minor_point =
        pointCalculator.StraightFlushAndUpdate();
    EXPECT_NE(kUnknown, minor_point);
    EXPECT_EQ(0x0C, minor_point);
  }
}

TEST_F(PointCalculatorTest, FullHouseTest) {}

TEST_F(PointCalculatorTest, FlushTest) {}

TEST_F(PointCalculatorTest, StraightTest) {}

TEST_F(PointCalculatorTest, ThreeTest) {}

TEST_F(PointCalculatorTest, TwoTest) {}

TEST_F(PointCalculatorTest, PairTest) {}

TEST_F(PointCalculatorTest, HighCardTest) {}

}  // namespace simulator
}  // namespace poker
