#include "components/poker/poker_game_controller/poker_landmark_generator/poker_landmark_generator.h"

#include <iostream>

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
  landmark_generator_(LandmarkRequestDataArray()) {}

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
}

}  // namespace poker
