#include "components/poker/poker_game_controller/landmark_finder/landmark_finder.h"

#include <iostream>

#include "google_test/testing_def.h"
#include "gtest/gtest.h"
#include "helpers/file_manager/file_manager.h"

namespace poker {

class LandmarkFinderTest : public testing::Test {
 public:
  LandmarkFinderTest() : landmark_finder_(6) {}

 protected:
  tester::Tester tester_;
  LandmarkFinder landmark_finder_;
};
TEST_F(LandmarkFinderTest, ConstructDestruct) {}

TEST_F(LandmarkFinderTest, FindPlayerCard) {
  std::string abs_path = tester_.GetAbsPath(tester::kBigImagePokerTable2);
  std::vector<char> raw_bytes =
      helpers::FileManager::ReadFile(abs_path.c_str());

  ASSERT_GT(static_cast<int>(raw_bytes.size()), 0);

  EXPECT_TRUE(landmark_finder_.UpdateBigImage(raw_bytes));
  Card card =
      landmark_finder_.FindLeftCard(PlayerLocation::PLAYERLOC_PLAYER_ZERO);
  EXPECT_EQ(card.card_value, CARD_VALUE_TEN);
  EXPECT_EQ(card.suit, SUIT_HEART);

  card = landmark_finder_.FindRightCard(PlayerLocation::PLAYERLOC_PLAYER_ZERO);
  EXPECT_EQ(card.card_value, CARD_VALUE_KING);
  EXPECT_EQ(card.suit, SUIT_CLUB);
}

TEST_F(LandmarkFinderTest, FindDealerCard) {
  std::string abs_path = tester_.GetAbsPath(tester::kBigImagePokerTable2);
  std::vector<char> raw_bytes =
      helpers::FileManager::ReadFile(abs_path.c_str());

  ASSERT_GT(static_cast<int>(raw_bytes.size()), 0);

  EXPECT_TRUE(landmark_finder_.UpdateBigImage(raw_bytes));
  Card card = landmark_finder_.FindDealerCard(DealerLocation::DEALER_ONE);
  EXPECT_EQ(card.card_value, CARD_VALUE_JACK);
  EXPECT_EQ(card.suit, SUIT_HEART);

  card = landmark_finder_.FindDealerCard(DealerLocation::DEALER_TWO);
  EXPECT_EQ(card.card_value, CARD_VALUE_FIVE);
  EXPECT_EQ(card.suit, SUIT_HEART);

  card = landmark_finder_.FindDealerCard(DealerLocation::DEALER_THREE);
  EXPECT_EQ(card.card_value, CARD_VALUE_QUEEN);
  EXPECT_EQ(card.suit, SUIT_CLUB);

  card = landmark_finder_.FindDealerCard(DealerLocation::DEALER_FOUR);
  EXPECT_EQ(card.card_value, CARD_VALUE_TEN);
  EXPECT_EQ(card.suit, SUIT_SPADE);

  card = landmark_finder_.FindDealerCard(DealerLocation::DEALER_FIVE);
  EXPECT_EQ(card.card_value, CARD_VALUE_FIVE);
  EXPECT_EQ(card.suit, SUIT_SPADE);
}

}  // namespace poker
