#include "components/poker/poker_game_controller/poker_landmark_generator/poker_landmark_generator.h"

#include <iostream>

#include "components/poker/poker_game_controller/definitions/six_player_config.h"
#include "google_test/testing_def.h"
#include "gtest/gtest.h"
#include "helpers/file_manager/file_manager.h"

namespace poker {

class PokerLandmarkGeneratorTest : public testing::Test {
 public:
  PokerLandmarkGeneratorTest()
      : testing_directory_(
            testing_main::kTestingDirectoryFromWorkspace,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        landmark_generator_(GenerateSixPlayerConfig()) {}

 protected:
  helpers::DirectoryFinder testing_directory_;
  PokerLandmarkGenerator landmark_generator_;
};
TEST_F(PokerLandmarkGeneratorTest, ConstructDestruct) {}

TEST_F(PokerLandmarkGeneratorTest, FindIndicatorTest) {
  // Get the big image of the poker table
  std::vector<char> bytes =
      helpers::FileManager::ReadFile(testing_directory_.GetAbsPathOfTargetFile(
          testing_main::kBigImagePokerTable));
  ASSERT_GT(static_cast<int>(bytes.size()), 0);

  const LandmarkResponseDataArray& landmark_response_data_array =
      landmark_generator_.GenerateRelativeToIndicator(bytes, 0, 0);
  const LandmarkResponseData& landmark_response_data =
      landmark_response_data_array[LANDMARK_PLAYER_ZERO];

  // Left card is a 7 of clubs
  EXPECT_TRUE(landmark_response_data.left_card.valid);
  std::cout << "landmark response left data "
            << landmark_response_data.left_card << std::endl;
  // Right card is a 3 of hearts
  EXPECT_TRUE(landmark_response_data.right_card.valid);
  std::cout << "landmark response right data "
            << landmark_response_data.right_card << std::endl;
}

}  // namespace poker
