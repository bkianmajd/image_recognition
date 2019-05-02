#include "components/poker/poker_game_controller/landmark_finder/table_locator/table_locator.h"

#include <iostream>

#include "gtest/gtest.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager.h"

namespace poker {
namespace {
constexpr int kTableSize = 6;

const std::string kTestingDirectory =
    "components/poker/poker_game_controller/landmark_finder/table_locator/"
    "test_data";

const std::string kTestImage = "testing_image.jpg";

}  // namespace

class TableLocatorTest : public testing::Test {
 public:
  TableLocatorTest()
      : directory_finder_(
            helpers::CreateDirectoryFinderFromWorkspace(kTestingDirectory)),
        table_locator_(kTableSize) {}

 protected:
  helpers::DirectoryFinder directory_finder_;
  TableLocator table_locator_;
  template_recognition::ScreenshotCreator screenshot_creator_;
};
TEST_F(TableLocatorTest, ConstructDestruct) {}

TEST_F(TableLocatorTest, DealerLocationTest) {
  // Load the table image
  std::vector<char> bytes = helpers::FileManager::ReadFile(
      directory_finder_.GetAbsPathOfTargetFile(kTestImage));
  screenshot_creator_.Capture(bytes);

  for (int dealer_loc = DealerLocation::DEALER_ONE;
       dealer_loc <= DealerLocation::DEALER_FIVE; dealer_loc++) {
    // Find the smaller image
    template_recognition::ScreenArea screen_area =
        table_locator_.GetDealerArea(static_cast<DealerLocation>(dealer_loc));

    // Captured the bytes
    std::vector<char> dealer_card_bytes =
        screenshot_creator_.GetLastCapture(screen_area);
    EXPECT_GT(dealer_card_bytes.size(), 0);
    std::stringstream output_ss;
    output_ss << dealer_loc << "_output.jpg";
    EXPECT_TRUE(helpers::FileManager::StoreFile(
        dealer_card_bytes.data(), dealer_card_bytes.size(),
        directory_finder_.GetAbsPathOfTargetFile(output_ss.str())));
  }
}

}  // namespace poker
