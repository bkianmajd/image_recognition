#include "libraries/image_trainer/trainer.h"

#include <iostream>

#include "gtest/gtest.h"
#include "helpers/file_manager/file_manager.h"

namespace image {
namespace {
const std::string kTestDirectory = "libraries/image_trainer/test_directory";
const std::string kSessionDirectory =
    "libraries/image_trainer/test_directory/session_directory";

}  // namespace

class TrainerTest : public testing::Test {
 public:
  TrainerTest()
      : test_directory_(
            helpers::CreateDirectoryFinderFromWorkspace(kTestDirectory)),
        trainer_(
            helpers::CreateDirectoryFinderFromWorkspace(kSessionDirectory)) {}

 protected:
  helpers::DirectoryFinder test_directory_;
  Trainer trainer_;
};

TEST_F(TrainerTest, ConstructDestruct) {}

TEST_F(TrainerTest, SplitTest) {
  std::pair<std::string, std::string> split = trainer_.SplitString("2_5.jpg");
  EXPECT_EQ(split.first, "2");
  EXPECT_EQ(split.second, "5");
}

TEST_F(TrainerTest, CreateFileNameTest) {
  std::string file_name = trainer_.CreateFileName(2, 5);
  EXPECT_EQ(file_name, "2_5.jpg");
}
TEST_F(TrainerTest, ConvertStringToIntTest) {
  int x = trainer_.ConvertStringToInt("2");
  EXPECT_EQ(x, 2);

  int xx = trainer_.ConvertStringToInt("5");
  EXPECT_EQ(xx, 5);
}

TEST_F(TrainerTest, IntegrationTest) {
  Image image = helpers::FileManager::ReadFile(
      test_directory_.GetAbsPathOfTargetFile("input.jpg"));
  ASSERT_GT(image.size(), 0);

  trainer_.AddImage(image);
  // Expect the sesion directory to be full of an image
}

}  // namespace image
