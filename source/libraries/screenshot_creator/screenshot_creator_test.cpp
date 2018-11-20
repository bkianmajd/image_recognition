#include "libraries/screenshot_creator/screenshot_creator.h"

#include <iostream>

#include "gtest/gtest.h"
#include "helpers/file_manager/file_manager.h"
#include "helpers/directory_finder.h"

namespace template_recognition {
namespace {

const std::string kDefaultTestFile = "test.jpg";
const std::string kScreenshotSaveFile = "screenshot.jpg";

}  // namespace

class ScreenshotCreatorTest : public testing::Test {
 public:
  ScreenshotCreatorTest()
      : test_directory_(
            "libraries/screenshot_creator/screenshots",
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace) {}

 protected:
  helpers::DirectoryFinder test_directory_;
  ScreenshotCreator screenshot_creator_;
};
TEST_F(ScreenshotCreatorTest, ConstructDestruct) {}

TEST_F(ScreenshotCreatorTest, CaptureTest) {
  EXPECT_TRUE(screenshot_creator_.Capture());

  std::vector<char> screenshot_raw_data = screenshot_creator_.GetLastCapture();
  EXPECT_GT(static_cast<int>(screenshot_raw_data.size()), 0);

  helpers::FileManager::StoreFile(
      screenshot_raw_data.data(), screenshot_raw_data.size(),
      test_directory_.GetAbsPathOfTargetFile(kDefaultTestFile));

  EXPECT_TRUE(screenshot_creator_.SaveLastCaptureToFile(
      test_directory_.GetAbsPathOfTargetFile(kScreenshotSaveFile)));
}

TEST_F(ScreenshotCreatorTest, CapturePortionTest) {
  EXPECT_TRUE(screenshot_creator_.Capture(100, 100, 500, 500));

  EXPECT_TRUE(screenshot_creator_.SaveLastCaptureToFile(
      test_directory_.GetAbsPathOfTargetFile(kScreenshotSaveFile)));
}

}  // namespace template_recognition
