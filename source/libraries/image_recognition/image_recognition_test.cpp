#include "libraries/image_recognition/image_recognition_api.h"

#include <iostream>

#include "google_test/testing_def.h"
#include "gtest/gtest.h"
#include "helpers/file_manager/file_manager.h"

namespace recognition {

const std::string kDefaultDirectory =
    "libraries/image_recognition/test_directory";
const std::string kTemplateDirectory =
    "libraries/image_recognition/test_directory/templates";

class ImageRecognitionApiTest : public testing::Test {
 public:
  ImageRecognitionApiTest()
      : testing_directory_(
            tester::kTestingDirectoryFromWorkspace,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        template_directory_(
            kTemplateDirectory,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        image_recognition_api_(template_directory_) {}

 protected:
  helpers::DirectoryFinder testing_directory_;
  helpers::DirectoryFinder template_directory_;
  ImageRecognitionApi image_recognition_api_;
};

TEST_F(ImageRecognitionApiTest, ConstructDestruct) {}

TEST_F(ImageRecognitionApiTest, BigImageTest) {
  std::vector<char> bytes = helpers::FileManager::ReadFile(
      testing_directory_.GetAbsPathOfTargetFile(tester::kBigImageCardDef));

  ASSERT_GT(static_cast<int>(bytes.size()), 0);

  EXPECT_TRUE(image_recognition_api_.SetBigImage(bytes));

  // Pont should be between 0-100, 100-200
  Point point = image_recognition_api_.TemplateMatch("3_hearts.jpg");
  EXPECT_TRUE(point.valid);
  EXPECT_GT(point.x, 0);
  EXPECT_LT(point.x, 100);
  EXPECT_GT(point.y, 100);
  EXPECT_LT(point.y, 200);

  // Point should be between 200-300, 500-600,
  point = image_recognition_api_.TemplateMatch("7_clubs.jpg");
  EXPECT_TRUE(point.valid);
  EXPECT_GT(point.x, 200);
  EXPECT_LT(point.x, 300);
  EXPECT_GT(point.y, 500);
  EXPECT_LT(point.y, 600);
}

TEST_F(ImageRecognitionApiTest, ImageTest) {
  // Get the big image of the poker table
  std::vector<char> bytes = helpers::FileManager::ReadFile(
      testing_directory_.GetAbsPathOfTargetFile(tester::kBigImagePokerTable));

  ASSERT_GT(static_cast<int>(bytes.size()), 0);

  EXPECT_TRUE(image_recognition_api_.SetBigImage(bytes));

  // Read all the poker table matches
  Point point = image_recognition_api_.TemplateMatch(tester::kTemplate3Hearts);
  EXPECT_TRUE(point.valid);
  std::cout << point << std::endl;

  point = image_recognition_api_.TemplateMatch(tester::kTemplate7Clubs);
  EXPECT_TRUE(point.valid);
  std::cout << point << std::endl;

  point = image_recognition_api_.TemplateMatch("FAIL.jpg");
  EXPECT_FALSE(point.valid);
  std::cout << point << std::endl;
}

TEST_F(ImageRecognitionApiTest, SecondImageTest) {
  // Get the big image of the poker table
  std::vector<char> bytes = helpers::FileManager::ReadFile(
      testing_directory_.GetAbsPathOfTargetFile(tester::kBigImagePokerTable2));

  ASSERT_GT(static_cast<int>(bytes.size()), 0);

  EXPECT_TRUE(image_recognition_api_.SetBigImage(bytes));

  // Read all the poker table matches
  Point point = image_recognition_api_.TemplateMatch("10_hearts.jpg");
  EXPECT_TRUE(point.valid);
  std::cout << "10_hearts.jpg " << point << std::endl;

  point = image_recognition_api_.TemplateMatch("j_hearts.jpg");
  EXPECT_TRUE(point.valid);
  std::cout << "j_hearts.jpg " << point << std::endl;

  point = image_recognition_api_.TemplateMatch("q_clubs.jpg");
  EXPECT_TRUE(point.valid);
  std::cout << "q_clubs.jpg " << point << std::endl;
}

}  // namespace recognition
