#include "components/session_manager/app_finder/app_finder.h"

#include <iostream>

#include "gtest/gtest.h"
#include "helpers/file_manager.h"

namespace poker {
namespace {
const std::string kTestingDirectory = "components/session_manager/app_finder/template";
const std::string kTestImage0 = "testing_0.jpg";
const std::string kTestImage1 = "testing_1.jpg";
const std::string kTestOutput = "testing_output.jpg";
}

class AppFinderTest : public testing::Test {
 public:
  AppFinderTest()
      : testing_direcetory_(
            kTestingDirectory,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace) {}

 protected:
  helpers::DirectoryFinder testing_direcetory_;
  AppFinder app_finder_;
};
TEST_F(AppFinderTest, ConstructDestruct) {}


TEST_F(AppFinderTest, NoSubsetTest) {
  std::vector<char> big_image = helpers::FileManager::ReadFile(
      testing_direcetory_.GetAbsPathOfTargetFile(kTestImage0));

  std::vector<char> smaller_image = app_finder_.Narrow(big_image);
  EXPECT_EQ(smaller_image.size(), 0);
}

TEST_F(AppFinderTest, SubsetTest) {
  std::vector<char> big_image = helpers::FileManager::ReadFile(
      testing_direcetory_.GetAbsPathOfTargetFile(kTestImage1));

  std::vector<char> smaller_image = app_finder_.Narrow(big_image);
  EXPECT_GT(smaller_image.size(), 0);
  helpers::FileManager::StoreFile(
      smaller_image.data(), smaller_image.size(),
      testing_direcetory_.GetAbsPathOfTargetFile(kTestOutput));
}

}  // namespace poker
