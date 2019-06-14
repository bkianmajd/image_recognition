#include "components/poker/statistics/winning_calculator/winning_calculator.h"

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

class WinningCalculatorTest : public testing::Test {
 public:
  WinningCalculatorTest()
      : cache_manager_(std::make_unique<CacheManager>(
            helpers::CreateDirectoryFinderFromWorkspace(kCacheDir),
            kTestPreflopCache, kTestPostflopCache)),
        winning_calculator_(cache_manager_.get()),
        player_hand_(Card(CARD_VALUE_ACE, SUIT_HEART),
                     Card(CARD_VALUE_THREE, SUIT_HEART)) {
    cache_manager_->Reset();
    cache_manager_->InitializeLoad();
  }

 protected:
  std::vector<Card> table_;
  std::unique_ptr<CacheManager> cache_manager_;
  WinningCalculator winning_calculator_;
  PlayerHand player_hand_;
};

TEST_F(WinningCalculatorTest, ConstructDestruct) {}

TEST_F(WinningCalculatorTest, PreflopTest) {
  // Expect nothing here
  base::Optional<double> result = cache_manager_->GetLosingProbability(
      player_hand_.FirstCard(), player_hand_.SecondCard());
  ASSERT_FALSE(result.has_value());

  // Expect this to calculate - takes  along time
  /*
    double winning_probability =
    winning_calculator_.GetWinningProbability(player_hand_, table_, 1); result =
    cache_manager_->GetLosingProbability(player_hand_.FirstCard(),
    player_hand_.SecondCard()); ASSERT_TRUE(result.has_value());


    // Stored in cache manager properly
    EXPECT_EQ(winning_probability, result);
  */

  // overwrite the cache manager
  const double kMockProb = .2;
  cache_manager_->StoreLosingProbability(player_hand_.FirstCard(),
                                         player_hand_.SecondCard(), kMockProb);
  result = cache_manager_->GetLosingProbability(player_hand_.FirstCard(),
                                                player_hand_.SecondCard());
  ASSERT_TRUE(result.has_value());
  double mock_winning_probability =
      winning_calculator_.GetWinningProbability(player_hand_, table_, 1);
  EXPECT_EQ(1 - kMockProb, mock_winning_probability);
}

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

TEST_F(WinningCalculatorTest, PostFlopTest) {
  // The player has an ace high flush
  table_.push_back(Card(CARD_VALUE_FOUR, SUIT_HEART));
  table_.push_back(Card(CARD_VALUE_SEVEN, SUIT_HEART));
  table_.push_back(Card(CARD_VALUE_TEN, SUIT_HEART));

  double flush_winning_probability = winning_calculator_.GetWinningProbability(
      player_hand_, table_, kOpponents);

  // The player has an ace high straight
  table_.clear();
  table_.push_back(Card(CARD_VALUE_FOUR, SUIT_SPADE));
  table_.push_back(Card(CARD_VALUE_TWO, SUIT_CLUB));
  table_.push_back(Card(CARD_VALUE_FIVE, SUIT_HEART));
  double straight_winning_probability =
      winning_calculator_.GetWinningProbability(player_hand_, table_,
                                                kOpponents);
  EXPECT_GT(flush_winning_probability, straight_winning_probability);
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
  double straight_winning_probability =
      winning_calculator_.GetWinningProbability(player_hand_, table_,
                                                kOpponents);
  EXPECT_GT(flush_winning_probability, straight_winning_probability);
}

}  // namespace statistics
}  // namespace poker
