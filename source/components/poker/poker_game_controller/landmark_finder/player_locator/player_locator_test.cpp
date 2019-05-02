#include "components/poker/poker_game_controller/landmark_finder/player_locator/player_locator.h"

#include <array>
#include <iostream>

#include "gtest/gtest.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager.h"

namespace poker {
namespace {
constexpr int kDefaultTableSize = 6;
const std::string kTestDirectory =
    "components/poker/poker_game_controller/landmark_finder/"
    "player_locator/test_data";
const std::string kImage = "test_image.jpg";
const std::string kImageTwo = "test_image_two.jpg";

std::array<PlayerLocator, kDefaultTableSize> CreateArray() {
  return std::array<PlayerLocator, kDefaultTableSize>{
      {PlayerLocator(kDefaultTableSize, PLAYERLOC_PLAYER_ZERO),
       PlayerLocator(kDefaultTableSize, PLAYERLOC_PLAYER_ONE),
       PlayerLocator(kDefaultTableSize, PLAYERLOC_PLAYER_TWO),
       PlayerLocator(kDefaultTableSize, PLAYERLOC_PLAYER_THREE),
       PlayerLocator(kDefaultTableSize, PLAYERLOC_PLAYER_FOUR),
       PlayerLocator(kDefaultTableSize, PLAYERLOC_PLAYER_FIVE)}};
}

}  // namespace

class PlayerLocatorTest : public testing::Test {
 public:
  PlayerLocatorTest()
      : player_locators_(CreateArray()),
        directory_finder_(
            kTestDirectory,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace) {}

 protected:
  std::array<PlayerLocator, kDefaultTableSize> player_locators_;
  helpers::DirectoryFinder directory_finder_;
  template_recognition::ScreenshotCreator screenshot_creator_;
};
TEST_F(PlayerLocatorTest, ConstructDestruct) {}

TEST_F(PlayerLocatorTest, PlayerAreaTest) {
  std::vector<char> bytes = helpers::FileManager::ReadFile(
      directory_finder_.GetAbsPathOfTargetFile(kImage.c_str()));
  screenshot_creator_.Capture(bytes);

  // Store screenshots
  for (size_t player_location = PlayerLocation::PLAYERLOC_PLAYER_ZERO;
       player_location < kDefaultTableSize; ++player_location) {
    template_recognition::ScreenArea smaller_area =
        player_locators_[player_location].GetPlayerArea();
    std::vector<char> smaller_bytes =
        screenshot_creator_.GetLastCapture(smaller_area);
    EXPECT_GT(smaller_bytes.size(), 0);

    std::stringstream ss;
    ss << player_location << ".jpg";
    helpers::FileManager::StoreFile(
        smaller_bytes.data(), smaller_bytes.size(),
        directory_finder_.GetAbsPathOfTargetFile(ss.str().c_str()));
  }
}

TEST_F(PlayerLocatorTest, PlayerAreaTestTwo) {
  std::vector<char> bytes = helpers::FileManager::ReadFile(
      directory_finder_.GetAbsPathOfTargetFile(kImageTwo.c_str()));
  screenshot_creator_.Capture(bytes);

  // Store screenshots
  for (size_t player_location = PlayerLocation::PLAYERLOC_PLAYER_ZERO;
       player_location < kDefaultTableSize; ++player_location) {
    template_recognition::ScreenArea smaller_area =
        player_locators_[player_location].GetPlayerArea();
    std::vector<char> smaller_bytes =
        screenshot_creator_.GetLastCapture(smaller_area);
    EXPECT_GT(smaller_bytes.size(), 0);

    std::stringstream ss;
    ss << "a" << player_location << ".jpg";
    helpers::FileManager::StoreFile(
        smaller_bytes.data(), smaller_bytes.size(),
        directory_finder_.GetAbsPathOfTargetFile(ss.str().c_str()));
  }
}

TEST_F(PlayerLocatorTest, CardAreaTest) {
  std::vector<char> bytes = helpers::FileManager::ReadFile(
      directory_finder_.GetAbsPathOfTargetFile(kImageTwo.c_str()));
  screenshot_creator_.Capture(bytes);

  size_t player_location = PlayerLocation::PLAYERLOC_PLAYER_FOUR;

  // Left card
  template_recognition::ScreenArea smaller_area =
      player_locators_[player_location].GetLeftCardArea();
  std::vector<char> smaller_bytes =
      screenshot_creator_.GetLastCapture(smaller_area);
  EXPECT_GT(smaller_bytes.size(), 0);
  std::stringstream ss;
  ss << "L" << player_location << ".jpg";
  helpers::FileManager::StoreFile(
      smaller_bytes.data(), smaller_bytes.size(),
      directory_finder_.GetAbsPathOfTargetFile(ss.str().c_str()));

  // Right card
  smaller_area = player_locators_[player_location].GetRightCardArea();
  smaller_bytes = screenshot_creator_.GetLastCapture(smaller_area);
  EXPECT_GT(smaller_bytes.size(), 0);
  std::stringstream ssr;
  ssr << "R" << player_location << ".jpg";
  helpers::FileManager::StoreFile(
      smaller_bytes.data(), smaller_bytes.size(),
      directory_finder_.GetAbsPathOfTargetFile(ssr.str().c_str()));
}

TEST_F(PlayerLocatorTest, CardAreaTest2) {
  std::vector<char> bytes = helpers::FileManager::ReadFile(
      directory_finder_.GetAbsPathOfTargetFile(kImageTwo.c_str()));
  screenshot_creator_.Capture(bytes);

  size_t player_location = PlayerLocation::PLAYERLOC_PLAYER_FIVE;

  // Left card
  template_recognition::ScreenArea smaller_area =
      player_locators_[player_location].GetLeftCardArea();
  std::vector<char> smaller_bytes =
      screenshot_creator_.GetLastCapture(smaller_area);
  EXPECT_GT(smaller_bytes.size(), 0);
  std::stringstream ss;
  ss << "L" << player_location << ".jpg";
  helpers::FileManager::StoreFile(
      smaller_bytes.data(), smaller_bytes.size(),
      directory_finder_.GetAbsPathOfTargetFile(ss.str().c_str()));

  // Right card
  smaller_area = player_locators_[player_location].GetRightCardArea();
  smaller_bytes = screenshot_creator_.GetLastCapture(smaller_area);
  EXPECT_GT(smaller_bytes.size(), 0);
  std::stringstream ssr;
  ssr << "R" << player_location << ".jpg";
  helpers::FileManager::StoreFile(
      smaller_bytes.data(), smaller_bytes.size(),
      directory_finder_.GetAbsPathOfTargetFile(ssr.str().c_str()));
}

}  // namespace poker
