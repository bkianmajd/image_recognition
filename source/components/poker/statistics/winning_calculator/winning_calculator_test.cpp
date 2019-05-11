#include "components/poker/statistics/winning_calculator/winning_calculator.h"

#include <iostream>

#include "gtest/gtest.h"

// referencing:
// https://www.cardplayer.com/poker-tools/odds-calculator/texas-holdem

namespace poker {
namespace statistics {
namespace {

constexpr int kOpponents = 1;
}

class WinningCalculatorTest : public testing::Test {
 public:
  WinningCalculatorTest()
      : player_hand_(Card(CARD_VALUE_ACE, SUIT_HEART),
                     Card(CARD_VALUE_THREE, SUIT_HEART)) {}

 protected:
  PlayerHand player_hand_;
  std::vector<Card> table_;
  WinningCalculator winning_calculator_;
};
TEST_F(WinningCalculatorTest, ConstructDestruct) {}

TEST_F(WinningCalculatorTest, LosingProbPostTurnTest) {
  double four_of_kind = 0;
  double open_ended_straight_draw = 0;
  double inside_straight_draw = 0;

  // Player has a four of a kind (aces) - simply the best combo possible. There
  // is no possibly for a straight flush
  {
    table_.push_back(Card(CARD_VALUE_ACE, SUIT_SPADE));
    table_.push_back(Card(CARD_VALUE_ACE, SUIT_CLUB));
    table_.push_back(Card(CARD_VALUE_ACE, SUIT_DIAMOND));
    table_.push_back(Card(CARD_VALUE_KING, SUIT_HEART));
    four_of_kind = winning_calculator_.GetWinningProbability(
        player_hand_, table_, kOpponents);
    EXPECT_EQ(1, four_of_kind);
  }

  // Player has a open ended straight draw, 2 or a seven
  {
    table_.clear();
    table_.push_back(Card(CARD_VALUE_FOUR, SUIT_SPADE));
    table_.push_back(Card(CARD_VALUE_FIVE, SUIT_CLUB));
    table_.push_back(Card(CARD_VALUE_SIX, SUIT_DIAMOND));
    table_.push_back(Card(CARD_VALUE_KING, SUIT_HEART));
    open_ended_straight_draw = winning_calculator_.GetWinningProbability(
        player_hand_, table_, kOpponents);
  }

  // Player has a open inside straight draw, only a 2
  {
    table_.clear();
    table_.push_back(Card(CARD_VALUE_JACK, SUIT_SPADE));
    table_.push_back(Card(CARD_VALUE_TEN, SUIT_CLUB));
    table_.push_back(Card(CARD_VALUE_FOUR, SUIT_DIAMOND));
    table_.push_back(Card(CARD_VALUE_FIVE, SUIT_HEART));
    inside_straight_draw = winning_calculator_.GetWinningProbability(
        player_hand_, table_, kOpponents);
  }

  // The open ended straight draw should have a higher probability of winning
  EXPECT_GT(open_ended_straight_draw, inside_straight_draw);
}

TEST_F(WinningCalculatorTest, PostTurnTest) {
  // The player has an ace high flush
  table_.push_back(Card(CARD_VALUE_FOUR, SUIT_SPADE));
  table_.push_back(Card(CARD_VALUE_SEVEN, SUIT_CLUB));
  table_.push_back(Card(CARD_VALUE_NINE, SUIT_HEART));
  table_.push_back(Card(CARD_VALUE_JACK, SUIT_HEART));
  table_.push_back(Card(CARD_VALUE_TEN, SUIT_HEART));

  double flush_winning_probability = winning_calculator_.GetWinningProbability(
      player_hand_, table_, kOpponents);

  // The player has an ace high straight
  table_.clear();
  table_.push_back(Card(CARD_VALUE_FOUR, SUIT_SPADE));
  table_.push_back(Card(CARD_VALUE_SEVEN, SUIT_CLUB));
  table_.push_back(Card(CARD_VALUE_NINE, SUIT_HEART));
  table_.push_back(Card(CARD_VALUE_JACK, SUIT_HEART));
  table_.push_back(Card(CARD_VALUE_TEN, SUIT_CLUB));
  double straight_winning_probability = winning_calculator_.GetWinningProbability(
      player_hand_, table_, kOpponents);
  EXPECT_GT(flush_winning_probability, straight_winning_probability);
}

}  // namespace statistics
}  // namespace poker
