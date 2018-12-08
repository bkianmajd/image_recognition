#include "components/poker/poker_game_controller/poker_landmark_generator/indicator_finder.h"

#include <iostream>

#include "google_test/testing_def.h"
#include "gtest/gtest.h"
#include "helpers/file_manager/file_manager.h"

namespace poker {

class IndicatorFinderTest : public testing::Test {
 public:
  IndicatorFinderTest()
      : testing_directory_(
            tester::kTestingDirectoryFromWorkspace,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace) {}

 protected:
  helpers::DirectoryFinder testing_directory_;
  IndicatorFinder indicator_finder_;
};
TEST_F(IndicatorFinderTest, ConstructDestruct) {}

TEST_F(IndicatorFinderTest, FindIndicatorTest) {
    std::vector<char> bytes;
  int indicator_x, indicator_y;

  // Get the big image of the poker table 1
  bytes =
      helpers::FileManager::ReadFile(testing_directory_.GetAbsPathOfTargetFile(
          tester::kBigImagePokerTable));
  ASSERT_GT(static_cast<int>(bytes.size()), 0);

  EXPECT_TRUE(
      indicator_finder_.FindIndicator(bytes, &indicator_x, &indicator_y));
  std::cout << "indicator (" << indicator_x << "," << indicator_y << ")"
            << std::endl;

  // Get the big image of the poker table 2
  bytes =
      helpers::FileManager::ReadFile(testing_directory_.GetAbsPathOfTargetFile(
          tester::kBigImagePokerTable2));
  ASSERT_GT(static_cast<int>(bytes.size()), 0);

  EXPECT_TRUE(
      indicator_finder_.FindIndicator(bytes, &indicator_x, &indicator_y));
  std::cout << "indicator (" << indicator_x << "," << indicator_y << ")"
            << std::endl;
}

}  // namespace poker
