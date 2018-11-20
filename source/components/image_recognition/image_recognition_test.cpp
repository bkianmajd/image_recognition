#include "components/image_recognition/image_recognition_api.h"

#include <iostream>

#include "google_test/testing_def.h"
#include "gtest/gtest.h"
#include "helpers/file_manager/file_manager.h"

namespace image_recognition {

const std::string kDefaultDirectory =
    "components/image_recognition/test_directory";

class ImageRecognitionApiTest : public testing::Test {
 public:
  ImageRecognitionApiTest()
      : testing_directory_(
            testing_main::kTestingDirectoryFromWorkspace,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        template_directory_(
            "libraries/model_generator/poker_model_generator/template_images",
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        session_directory_(
            kDefaultDirectory,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        image_recognition_api_(template_directory_, session_directory_) {}

 protected:
  helpers::DirectoryFinder testing_directory_;
  helpers::DirectoryFinder template_directory_;
  helpers::DirectoryFinder session_directory_;
  ImageRecognitionApi image_recognition_api_;
};

TEST_F(ImageRecognitionApiTest, ConstructDestruct) {}

TEST_F(ImageRecognitionApiTest, ImageTest) {
  // Get the big image of the poker table
  std::vector<char> bytes =
      helpers::FileManager::ReadFile(testing_directory_.GetAbsPathOfTargetFile(
          testing_main::kBigImagePokerTable));

  ASSERT_GT(static_cast<int>(bytes.size()), 0);

  EXPECT_TRUE(image_recognition_api_.SetBigImage(bytes));

  // Read all the poker table matches
  Point point =
      image_recognition_api_.TemplateMatch(testing_main::kTemplate3Hearts);
  EXPECT_TRUE(point.valid);
  std::cout << point << std::endl;

  point = image_recognition_api_.TemplateMatch(testing_main::kTemplate7Clubs);
  EXPECT_TRUE(point.valid);
  std::cout << point << std::endl;

  point = image_recognition_api_.TemplateMatch("3_clubs.jpg");
  EXPECT_FALSE(point.valid);
  std::cout << point << std::endl;

  point = image_recognition_api_.TemplateMatch(testing_main::kTemplateCheckers);
  EXPECT_FALSE(point.valid);
  std::cout << point << std::endl;
}

TEST_F(ImageRecognitionApiTest, SecondImageTest) {
  // Get the big image of the poker table
  std::vector<char> bytes =
      helpers::FileManager::ReadFile(testing_directory_.GetAbsPathOfTargetFile(
          testing_main::kBigImagePokerTable2));

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

  point = image_recognition_api_.TemplateMatch("5_spades.jpg");
  EXPECT_TRUE(point.valid);
  std::cout << "5_spades.jpg " << point << std::endl;

  point = image_recognition_api_.TemplateMatch("5_clubs.jpg");
  EXPECT_FALSE(point.valid);
  std::cout << "5_clubs.jpg " << point << std::endl;

  point = image_recognition_api_.TemplateMatch("4_spades.jpg");
  EXPECT_FALSE(point.valid);
  std::cout << "4_spades.jpg " << point << std::endl;

  point = image_recognition_api_.TemplateMatch("3_spades.jpg");
  EXPECT_FALSE(point.valid);
  std::cout << "3_spades.jpg " << point << std::endl;

  point = image_recognition_api_.TemplateMatch("2_spades.jpg");
  EXPECT_FALSE(point.valid);
  std::cout << "2_spades.jpg " << point << std::endl;

  point = image_recognition_api_.TemplateMatch("6_spades.jpg");
  EXPECT_FALSE(point.valid);
  std::cout << "6_spades.jpg " << point << std::endl;

  point = image_recognition_api_.TemplateMatch("7_spades.jpg");
  EXPECT_FALSE(point.valid);
  std::cout << "7_spades.jpg " << point << std::endl;
}

}  // namespace image_recognition
