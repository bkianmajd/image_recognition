#include "libraries/image_file_manager/image_file_manager.h"

#include <iostream>

#include "google_test/testing_def.h"
#include "gtest/gtest.h"
#include "helpers/file_manager/file_manager.h"

namespace image_recognition {

class ImageFileManagerTest : public testing::Test {
 public:
  ImageFileManagerTest()
      : session_directory_(
            "libraries/image_file_manager/test_directory",
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        image_file_manager_(session_directory_) {}

 protected:
  helpers::DirectoryFinder session_directory_;
  ImageFileManager image_file_manager_;
};

TEST_F(ImageFileManagerTest, ConstructDestruct) {}

TEST_F(ImageFileManagerTest, RemoveStoreImageTest) {
  helpers::DirectoryFinder test_directory(
      testing_main::kTestingDirectoryFromWorkspace,
      helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace);

  std::string abs_image_path =
      test_directory.GetAbsPathOfTargetFile(testing_main::kBigImage);
  // Grab the raw data
  std::vector<char> image_bytes =
      helpers::FileManager::ReadFile(abs_image_path);
  ASSERT_GT(image_bytes.size(), 0);

  // First remove if test_image is already in the sesion directory.
  image_file_manager_.RemoveImage(testing_main::kBigImage);

  // Next store the image
  EXPECT_TRUE(
      image_file_manager_.StoreImage(testing_main::kBigImage, image_bytes));
}

}  // namespace helpers
