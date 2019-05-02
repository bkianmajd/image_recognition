#include "components/poker/poker_game_controller/landmark_finder/landmark_finder.h"

#include <iostream>

#include "google_test/testing_def.h"
#include "gtest/gtest.h"
#include "helpers/file_manager.h"

namespace poker {
namespace {
const std::string kTestDirectory =
    "components/poker/poker_game_controller/landmark_finder/test_data";
}  // namespace

class LandmarkFinderTest : public testing::Test {
 public:
  LandmarkFinderTest()
      : directory_finder_(
            helpers::CreateDirectoryFinderFromWorkspace(kTestDirectory)),
        landmark_finder_(6) {}

 protected:
  helpers::DirectoryFinder directory_finder_;
  LandmarkFinder landmark_finder_;
};
TEST_F(LandmarkFinderTest, ConstructDestruct) {}

TEST_F(LandmarkFinderTest, FindPlayerCard) {
  // Card reader should return a card
}

TEST_F(LandmarkFinderTest, FindDealerCard) {
  // Card reader should return a card
}

}  // namespace poker
