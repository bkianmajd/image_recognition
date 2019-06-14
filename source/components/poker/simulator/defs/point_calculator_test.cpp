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
  std::array<Card, 7> unsorted_cards_;
};

TEST_F(PointCalculatorTest, ConstructDestruct) {
  size_t i = 0;
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_TEN, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
  unsorted_cards_[i++] = Card(CARD_VALUE_SEVEN, SUIT_HEART);
  PointCalculator pointCalculator(unsorted_cards_);
}

TEST_F(PointCalculatorTest, PointTest) {
  Points flush;
  Points straigh;
  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_TEN, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_SEVEN, SUIT_HEART);
    PointCalculator pointCalculator(unsorted_cards_);
    flush = pointCalculator.GetPoints();
  }
  size_t i = 0;
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_SPADE);
  unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
  PointCalculator pointCalculator(unsorted_cards_);
  Points straight = pointCalculator.GetPoints();

  EXPECT_GT(flush, straight);
}

TEST_F(PointCalculatorTest, SortTest) {
  size_t i = 0;
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_TEN, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_DIAMOND);
  PointCalculator pointCalculator(unsorted_cards_);

  EXPECT_EQ(unsorted_cards_.size(), pointCalculator.value_sorted_cards_.size());

  EXPECT_EQ(CARD_VALUE_TWO, pointCalculator.value_sorted_cards_[0].value);
  EXPECT_EQ(CARD_VALUE_THREE, pointCalculator.value_sorted_cards_[1].value);
  EXPECT_EQ(CARD_VALUE_TEN, pointCalculator.value_sorted_cards_[2].value);
  EXPECT_EQ(CARD_VALUE_KING, pointCalculator.value_sorted_cards_[3].value);
  EXPECT_EQ(CARD_VALUE_ACE, pointCalculator.value_sorted_cards_[4].value);
  EXPECT_EQ(CARD_VALUE_ACE, pointCalculator.value_sorted_cards_[5].value);
}

TEST_F(PointCalculatorTest, ValueMapTest) {
  size_t i = 0;
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_SPADE);
  unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_HEART);
  unsorted_cards_[i++] = Card(CARD_VALUE_TEN, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
  PointCalculator pointCalculator(unsorted_cards_);

  EXPECT_EQ(2, pointCalculator.value_map_.at(CARD_VALUE_ACE));
  EXPECT_EQ(1, pointCalculator.value_map_.at(CARD_VALUE_TWO));
  EXPECT_EQ(3, pointCalculator.value_map_.at(CARD_VALUE_THREE));
  EXPECT_EQ(1, pointCalculator.value_map_.at(CARD_VALUE_TEN));
}

TEST_F(PointCalculatorTest, RoyalFlushTest) {
  size_t i = 0;
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_JACK, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_QUEEN, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_HEART);
  unsorted_cards_[i++] = Card(CARD_VALUE_TEN, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
  PointCalculator pointCalculator(unsorted_cards_);
  EXPECT_NE(kUnknown, pointCalculator.RoyalFlush());
  EXPECT_NE(kFalse, pointCalculator.RoyalFlush());
  EXPECT_GT(pointCalculator.RoyalFlush(), 0);

  i = 0;
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_JACK, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_QUEEN, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_SPADE);
  unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_TEN, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_SPADE);
  PointCalculator pointCalculator2(unsorted_cards_);
  EXPECT_EQ(kFalse, pointCalculator2.RoyalFlush());
}

TEST_F(PointCalculatorTest, FourTest) {
  size_t i = 0;
  unsorted_cards_[i++] = Card(CARD_VALUE_JACK, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_JACK, SUIT_HEART);
  unsorted_cards_[i++] = Card(CARD_VALUE_JACK, SUIT_SPADE);
  unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_HEART);
  unsorted_cards_[i++] = Card(CARD_VALUE_JACK, SUIT_DIAMOND);
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
  PointCalculator pointCalculator(unsorted_cards_);
  PointCalculator::MinorPoint minor_point =
      pointCalculator.FourOfAKindAndUpdate();
  EXPECT_NE(kUnknown, minor_point);
  EXPECT_NE(kFalse, minor_point);
  EXPECT_GT(minor_point, 0);

  i = 0;
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_JACK, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_QUEEN, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_SPADE);
  unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_TEN, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_SPADE);
  PointCalculator pointCalculator2(unsorted_cards_);
  EXPECT_EQ(kFalse, pointCalculator2.FourOfAKindAndUpdate());
}

TEST_F(PointCalculatorTest, StraightFlushTest) {
  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
    PointCalculator pointCalculator(unsorted_cards_);
    PointCalculator::MinorPoint minor_point =
        pointCalculator.StraightFlushAndUpdate();
    EXPECT_NE(kUnknown, minor_point);
    EXPECT_GT(minor_point, 0);
  }

  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
    PointCalculator pointCalculator2(unsorted_cards_);
    EXPECT_EQ(kFalse, pointCalculator2.StraightFlushAndUpdate());
  }

  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_NINE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_TEN, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_JACK, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_QUEEN, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_EIGHT, SUIT_HEART);
    PointCalculator pointCalculator(unsorted_cards_);
    PointCalculator::MinorPoint minor_point =
        pointCalculator.StraightFlushAndUpdate();
    EXPECT_NE(kUnknown, minor_point);
    EXPECT_EQ(0x0C, minor_point);
  }
}

TEST_F(PointCalculatorTest, FullHouseTest) {
  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_SPADE);
    unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_HEART);
    PointCalculator pointCalculator(unsorted_cards_);
    pointCalculator.UpdatePair();
    pointCalculator.UpdateThreeOfKind();
    PointCalculator::MinorPoint minor_point = pointCalculator.FullHouse();
    EXPECT_NE(kUnknown, minor_point);
    // A - 10, B - Jack, C - Queen, D - King, E - Ace
    // Aces full of kings
    EXPECT_EQ(0xED, minor_point);
  }

  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_SPADE);
    unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_HEART);
    PointCalculator pointCalculator(unsorted_cards_);
    pointCalculator.UpdatePair();
    pointCalculator.UpdateThreeOfKind();
    PointCalculator::MinorPoint minor_point = pointCalculator.FullHouse();
    EXPECT_NE(kUnknown, minor_point);
    // A - 10, B - Jack, C - Queen, D - King, E - Ace
    // King full of aces
    EXPECT_EQ(0xDE, minor_point);
  }
}

TEST_F(PointCalculatorTest, FlushTest) {
  size_t i = 0;
  unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_QUEEN, SUIT_CLUB);
  PointCalculator pointCalculator(unsorted_cards_);
  PointCalculator::MinorPoint minor_point = pointCalculator.Flush();
  EXPECT_NE(kUnknown, minor_point);
  // A - 10, B - Jack, C - Queen, D - King, E - Ace

  // Ace, king, queen, five, four
  EXPECT_EQ(0x0EDC54, minor_point);
}

TEST_F(PointCalculatorTest, StraightTest) {
  {  // Ace high
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_TEN, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_JACK, SUIT_SPADE);
    unsorted_cards_[i++] = Card(CARD_VALUE_QUEEN, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_EIGHT, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_NINE, SUIT_CLUB);
    PointCalculator pointCalculator(unsorted_cards_);
    PointCalculator::MinorPoint minor_point = pointCalculator.Straight();
    // A - 10, B - Jack, C - Queen, D - King, E - Ace
    EXPECT_EQ(0x0E, minor_point);
  }

  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_SIX, SUIT_SPADE);
    unsorted_cards_[i++] = Card(CARD_VALUE_SEVEN, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_EIGHT, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_NINE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
    PointCalculator pointCalculator(unsorted_cards_);
    PointCalculator::MinorPoint minor_point = pointCalculator.Straight();
    // A - 10, B - Jack, C - Queen, D - King, E - Ace
    EXPECT_EQ(0x09, minor_point);
  }

  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_KING, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_QUEEN, SUIT_SPADE);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
    PointCalculator pointCalculator(unsorted_cards_);
    PointCalculator::MinorPoint minor_point = pointCalculator.Straight();
    EXPECT_NE(kUnknown, minor_point);
    // A - 10, B - Jack, C - Queen, D - King, E - Ace
    EXPECT_EQ(0x05, minor_point);
  }
}

TEST_F(PointCalculatorTest, ThreeTest) {
  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_SPADE);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
    PointCalculator pointCalculator(unsorted_cards_);
    pointCalculator.UpdateThreeOfKind();
    PointCalculator::MinorPoint minor_point = pointCalculator.ThreeOfAKind();
    EXPECT_NE(kUnknown, minor_point);
    // A - 10, B - Jack, C - Queen, D - King, E - Ace
    EXPECT_EQ(0x0E54, minor_point);
  }
}

TEST_F(PointCalculatorTest, TwoTest) {
  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_SPADE);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
    PointCalculator pointCalculator(unsorted_cards_);
    // Need to register pair first to load the cache
    pointCalculator.FourOfAKindAndUpdate();
    PointCalculator::MinorPoint minor_point = pointCalculator.TwoPair();
    EXPECT_NE(kUnknown, minor_point);
    // A - 10, B - Jack, C - Queen, D - King, E - Ace
    // Aces and two
    EXPECT_EQ(0xE25, minor_point);
  }

  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_SPADE);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
    PointCalculator pointCalculator(unsorted_cards_);
    pointCalculator.FourOfAKindAndUpdate();
    PointCalculator::MinorPoint minor_point = pointCalculator.TwoPair();
    EXPECT_NE(kUnknown, minor_point);
    // A - 10, B - Jack, C - Queen, D - King, E - Ace
    // Five and two
    EXPECT_EQ(0x52E, minor_point);
  }
}

TEST_F(PointCalculatorTest, PairTest) {
  size_t i = 0;
  unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_HEART);
  unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_SPADE);
  unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_CLUB);
  unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
  PointCalculator pointCalculator(unsorted_cards_);
  pointCalculator.FourOfAKindAndUpdate();
  PointCalculator::MinorPoint minor_point = pointCalculator.Pair();
  EXPECT_EQ(0x05E43, minor_point);
}

TEST_F(PointCalculatorTest, HighCardTest) {
  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_ACE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_SPADE);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_QUEEN, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
    PointCalculator pointCalculator(unsorted_cards_);
    PointCalculator::MinorPoint minor_point = pointCalculator.HighCard();
    EXPECT_EQ(0x0EC543, minor_point);
  }

  {
    size_t i = 0;
    unsorted_cards_[i++] = Card(CARD_VALUE_SIX, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FIVE, SUIT_HEART);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_SPADE);
    unsorted_cards_[i++] = Card(CARD_VALUE_TWO, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_FOUR, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_NINE, SUIT_CLUB);
    unsorted_cards_[i++] = Card(CARD_VALUE_THREE, SUIT_CLUB);
    PointCalculator pointCalculator(unsorted_cards_);
    PointCalculator::MinorPoint minor_point = pointCalculator.HighCard();
    EXPECT_EQ(0x096543, minor_point);
  }
}

}  // namespace simulator
}  // namespace poker
