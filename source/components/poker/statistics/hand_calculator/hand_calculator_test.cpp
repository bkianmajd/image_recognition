#include "components/poker/statistics/hand_calculator/hand_calculator.h"

#include <iostream>

#include "gtest/gtest.h"

// referencing:
// https://www.cardplayer.com/poker-tools/odds-calculator/texas-holdem

namespace poker {
namespace statistics {
namespace {

constexpr int kOpponents = 1;
const std::string kCacheDir =
    "components/poker/statistics/cache_manager/binary_data";
const std::string kTestPreflopCache = "testPreflop.dat";
const std::string kTestPostflopCache = "testPostflop.dat";

}  // namespace

class HandCalculatorTest : public testing::Test {
 public:
  HandCalculatorTest()
      : player_hand_(Card(CARD_VALUE_ACE, SUIT_HEART),
                     Card(CARD_VALUE_THREE, SUIT_HEART)) {}

 protected:
  HandCalculator hand_calculator_;
  PlayerHand player_hand_;
  Table table_;
};

TEST_F(HandCalculatorTest, ConstructDestruct) {}

TEST_F(HandCalculatorTest, PreflopTest) {
  HandStatistic hand_statistic =
      hand_calculator_.CalculateHandProbability(player_hand_, table_, 1);

  // Expect losing prob to be greater than tieing prob
  EXPECT_GT(hand_statistic.losing_probability, hand_statistic.tie_probability);
}

TEST_F(HandCalculatorTest, PostFlopTest) {
  // The player has an ace high flush
  table_.cards_[0] = Card(CARD_VALUE_FOUR, SUIT_HEART);
  table_.cards_[1] = Card(CARD_VALUE_SEVEN, SUIT_HEART);
  table_.cards_[2] = Card(CARD_VALUE_TEN, SUIT_HEART);

  HandStatistic hand_statistic =
      hand_calculator_.CalculateHandProbability(player_hand_, table_, 1);

  // Expect losing prob to be greater than tieing prob
  EXPECT_GT(hand_statistic.losing_probability, hand_statistic.tie_probability);
}

TEST_F(HandCalculatorTest, LosingProbPostTurnTest) {
  // The player has an ace high flush
  table_.cards_[0] = Card(CARD_VALUE_FOUR, SUIT_HEART);
  table_.cards_[1] = Card(CARD_VALUE_SEVEN, SUIT_HEART);
  table_.cards_[2] = Card(CARD_VALUE_TEN, SUIT_HEART);
  table_.cards_[3] = Card(CARD_VALUE_NINE, SUIT_HEART);

  HandStatistic hand_statistic =
      hand_calculator_.CalculateHandProbability(player_hand_, table_, 1);

  // Expect losing prob to be greater than tieing prob
  EXPECT_GT(hand_statistic.losing_probability, hand_statistic.tie_probability);
}

TEST_F(HandCalculatorTest, PostTurnTest) {
  // The player has an ace high flush
  table_.cards_[0] = Card(CARD_VALUE_FOUR, SUIT_HEART);
  table_.cards_[1] = Card(CARD_VALUE_SEVEN, SUIT_HEART);
  table_.cards_[2] = Card(CARD_VALUE_TEN, SUIT_HEART);
  table_.cards_[3] = Card(CARD_VALUE_NINE, SUIT_HEART);
  table_.cards_[4] = Card(CARD_VALUE_SIX, SUIT_HEART);

  HandStatistic hand_statistic =
      hand_calculator_.CalculateHandProbability(player_hand_, table_, 1);

  // Expect losing prob to be greater than tieing prob
  EXPECT_GT(hand_statistic.losing_probability, hand_statistic.tie_probability);
}

}  // namespace statistics
}  // namespace poker
