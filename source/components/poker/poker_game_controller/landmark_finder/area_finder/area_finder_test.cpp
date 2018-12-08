#include "components/poker/poker_game_controller/landmark_finder/area_finder/area_finder.h"

#include <iostream>
#include <sstream>

#include "components/poker/poker_game_controller/landmark_finder/area_finder/six_player_area_finder.h"
#include "google_test/testing_def.h"
#include "gtest/gtest.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager/file_manager.h"

namespace poker {
namespace {
const std::string kOutputDirectory =
    "components/poker/poker_game_controller/landmark_finder/area_finder/"
    "test_areas";
}  // namespece

class AreaFinderTest : public testing::Test {
 public:
  AreaFinderTest()
      : output_directory_(
            kOutputDirectory,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace) {}

  // This is outside of the scope of this unit test
  void OutputToFile(const template_recognition::ScreenArea& screen_area) {
    std::vector<char> subset_bytes =
        screenshot_creator_.GetLastCapture(screen_area);

    // output the image
    std::stringstream ss;
    ss << "img" << image_number_++ << ".jpg";
    helpers::FileManager::StoreFile(
        subset_bytes.data(), subset_bytes.size(),
        output_directory_.GetAbsPathOfTargetFile(ss.str()));
  }

 protected:
  SixPlayerAreaFinder six_player_area_finder_;
  tester::Tester tester_;
  helpers::DirectoryFinder output_directory_;
  template_recognition::ScreenshotCreator screenshot_creator_;
  int image_number_ = 1;
};

TEST_F(AreaFinderTest, ConstructDestruct) {}

TEST_F(AreaFinderTest, FindAreaTest) {
  template_recognition::ScreenArea screen_area =
      six_player_area_finder_.GetCardAreaLeft(
          PlayerLocation::PLAYERLOC_PLAYER_ZERO);
  EXPECT_GT(screen_area.height, 0);
  EXPECT_GT(screen_area.width, 0);
}

TEST_F(AreaFinderTest, ScreenshotPlayerTest) {
  PlayerLocation player_location = PlayerLocation::PLAYERLOC_PLAYER_ONE;

  std::string abs_path = tester_.GetAbsPath(tester::kBigImagePokerTable2);
  std::vector<char> raw_bytes = helpers::FileManager::ReadFile(abs_path);
  screenshot_creator_.Capture(raw_bytes);

  template_recognition::ScreenArea screen_area;

  screen_area = six_player_area_finder_.GetCardAreaLeft(player_location);
  OutputToFile(screen_area);

  screen_area = six_player_area_finder_.GetCardAreaRight(player_location);
  OutputToFile(screen_area);

  screen_area = six_player_area_finder_.GetPlayerArea(player_location);
  OutputToFile(screen_area);

  screen_area = six_player_area_finder_.GetMoneyArea(player_location);
  OutputToFile(screen_area);
}

}  // namespace poker
