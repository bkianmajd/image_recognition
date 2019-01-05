#include "libraries/image_pipeline/filter/noise_reducer.h"

#include <iostream>

#include "gtest/gtest.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager/file_manager.h"
#include "libraries/image_def/image_def.h"
#include "libraries/image_def/utility/utility.h"

namespace image {
namespace {
const std::string kTestDirectory = "libraries/image_pipeline/filter/test_data/";
}  // namespace

class ImageFilterTest : public testing::Test {
 public:
  ImageFilterTest()
      : directory_finder_(
            helpers::CreateDirectoryFinderFromWorkspace(kTestDirectory)) {}

 protected:
  helpers::DirectoryFinder directory_finder_;
};
TEST_F(ImageFilterTest, ConstructDestruct) {}

TEST_F(ImageFilterTest, TestData) {
  std::vector<char> bytes = helpers::FileManager::ReadFile(
      directory_finder_.GetAbsPathOfTargetFile("input.jpg"));
  Image& image = bytes;

  ASSERT_GT(bytes.size(), 0);
  cv::Mat mat = image::ConvertImageToMatrix(image);
  image::FilterNoiseMatrix(&mat);

  Image output = image::ConvertToRawBytes(mat);
  EXPECT_GT(output.size(), 0);
  helpers::FileManager::StoreFile(
      output.data(), output.size(),
      directory_finder_.GetAbsPathOfTargetFile("output.jpg"));
}

}  // namespace image
