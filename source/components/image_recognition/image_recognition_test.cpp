#include "components/image_recognition/image_recognition_api.h"

#include <iostream>

#include "google_test/testing_def.h"
#include "gtest/gtest.h"
#include "helpers/file_manager/file_manager.h"

namespace image_recognition {

class ImageRecognitionApiTest : public testing::Test {
 public:
  ImageRecognitionApiTest()
      : template_directory_(
            testing_main::kTestingDirectoryFromWorkspace,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        image_recognition_api_(template_directory_) {}

 protected:
  helpers::DirectoryFinder template_directory_;
  ImageRecognitionApi image_recognition_api_;
};

TEST_F(ImageRecognitionApiTest, ConstructDestruct) {}

TEST_F(ImageRecognitionApiTest, ImageTest) {
  // Get the big image of the poker table
  std::vector<char> bytes =
      helpers::FileManager::ReadFile(template_directory_.GetAbsPathOfTargetFile(
          testing_main::kBigImagePokerTable));

  ASSERT_GT(bytes.size(), 0);

  EXPECT_TRUE(image_recognition_api_.SetBigImage(bytes));

  // Read all the poker table matches
  Point point =
      image_recognition_api_.TemplateMatch(testing_main::kTemplate3Hearts);
  EXPECT_TRUE(point.valid);
  std::cout << point << std::endl;

  point = image_recognition_api_.TemplateMatch(testing_main::kTemplate7Clubs);
  EXPECT_TRUE(point.valid);
  std::cout << point << std::endl;

  point = image_recognition_api_.TemplateMatch(testing_main::kTemplateCheckers);
  EXPECT_FALSE(point.valid);
  std::cout << point << std::endl;
}

}  // namespace image_recognition
