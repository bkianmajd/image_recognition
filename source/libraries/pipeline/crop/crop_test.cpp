#include "gtest/gtest.h"

#include <iostream>

#include "helpers/directory_finder.h"
#include "helpers/file_manager/file_manager.h"
#include "libraries/image_def/image_def.h"
#include "libraries/pipeline/crop/vertical_crop.h"
#include "libraries/pipeline/utility/utility.h"

namespace image {
namespace {
const std::string kTestDirectory = "libraries/pipeline/crop/test_data";
}  // namespace

class CropTest : public testing::Test {
 public:
  CropTest()
      : directory_finder_(
            helpers::CreateDirectoryFinderFromWorkspace(kTestDirectory)) {}

 protected:
  helpers::DirectoryFinder directory_finder_;
};

TEST_F(CropTest, ConstructDestruct) {}

TEST_F(CropTest, VerticalCropTest) {
  std::vector<char> raw_bytes = helpers::FileManager::ReadFile(
      directory_finder_.GetAbsPathOfTargetFile("vert_input.jpg"));
  const Image& image = raw_bytes;

  // Convert image to matrix and run a vertical crop
  ASSERT_GT(image.size(), 0);
  cv::Mat mat = image::ConvertImageToMatrix(image);
  std::vector<cv::Mat> cropped = image::VerticalCrop(mat);
  EXPECT_EQ(cropped.size(), 2);

  // Output matrix
  int output_number = 0;
  for (cv::Mat output : cropped) {
    std::stringstream ss;
    ss << "out_" << output_number++ << ".jpg";
    Image image = image::ConvertToRawBytes(output);
    if (image.size() == 0) {
      FAIL();
    }
    helpers::FileManager::StoreFile(
        image.data(), image.size(),
        directory_finder_.GetAbsPathOfTargetFile(ss.str()));
  }
}

TEST_F(CropTest, VerticalCropTest2) {
  std::vector<char> raw_bytes = helpers::FileManager::ReadFile(
      directory_finder_.GetAbsPathOfTargetFile("vert_input.jpg"));
  const Image& image = raw_bytes;

  // Convert image to matrix and run a vertical crop
  ASSERT_GT(image.size(), 0);
  cv::Mat mat = image::ConvertImageToMatrix(image);
  std::vector<cv::Mat> matrix_vector;
  matrix_vector.push_back(mat);
  matrix_vector.push_back(mat);

  // Vertical crop should take 2 matricies and convert them into 4 matricies
  image::VerticalCrop(&matrix_vector);

  // Expect 4
  EXPECT_EQ(matrix_vector.size(), 4);
}

}  // namespace image
