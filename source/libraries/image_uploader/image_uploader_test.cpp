#include "libraries/image_uploader/image_uploader.h"

#include <iostream>

#include "google_test/testing_def.h"
#include "gtest/gtest.h"

namespace image {

class ImageUploaderTest : public testing::Test {
 public:
  ImageUploaderTest()
      : image_uploader_(helpers::CreateDirectoryFinderFromWorkspace(
            tester::kTestingDirectoryFromWorkspace)) {}
  ~ImageUploaderTest() = default;

 protected:
  ImageUploader image_uploader_;
};

TEST_F(ImageUploaderTest, ConstructDestruct) {}

TEST_F(ImageUploaderTest, GetImageListTest) {
  QStringList image_list = image_uploader_.GetImageList();
  EXPECT_GT(image_list.size(), 0);
}

}  // namespace image
