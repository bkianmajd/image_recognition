#include "components/poker/poker_game_controller/landmark_finder/landmark_finder.h"

#include <iostream>

#include "gtest/gtest.h"
#include "google_test/testing_def.h"
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

TEST_F(LandmarkFinderTest, FindCard) {
  std::string abs_path = tester_.GetAbsPath(tester::kBigImagePokerTable2);
  std::vector<char> raw_bytes = helpers::FileManager::ReadFile(abs_path.c_str());

  ASSERT_GT(raw_bytes.size(), 0);

  EXPECT_TRUE(landmark_finder_.UpdateBigImage(raw_bytes));
  Card card = landmark_finder_.FindLeftCard(PlayerLocation::PLAYERLOC_PLAYER_ZERO);

  std::cout << "card value " << card.card_value << std::endl;
}

}  // namespace poker
