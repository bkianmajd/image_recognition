#include "libraries/image_comparer/comparer.h"

#include <chrono>
#include <iostream>

#include "gtest/gtest.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager/file_manager.h"

namespace image {
namespace {
const std::string kTestDirectory = "libraries/image_comparer/test_data";
const std::string kTemplateDirectory =
    "libraries/image_comparer/test_data/template_directory";

const std::string kFileName1 = "img_1.jpg";
}  // namespace

class ComparerTest : public testing::Test {
 public:
  ComparerTest()
      : directory_finder_(
            helpers::CreateDirectoryFinderFromWorkspace(kTestDirectory)),
        comparer_(
            helpers::CreateDirectoryFinderFromWorkspace(kTemplateDirectory)) {}

 protected:
  helpers::DirectoryFinder directory_finder_;
  Comparer comparer_;
};
TEST_F(ComparerTest, ConstructDestruct) {}

TEST_F(ComparerTest, CompareImageTest) {
  Image image = helpers::FileManager::ReadFile(
      directory_finder_.GetAbsPathOfTargetFile(kFileName1));

  ASSERT_GT(image.size(), 0);
  EXPECT_TRUE(comparer_.LoadCache());

  // Expect to see img_1.jpg
  std::string found_name = comparer_.FindImageInDirectory(image);
  EXPECT_EQ(kFileName1, found_name);
}

TEST_F(ComparerTest, CompareNoImageTest) {
  Image image = helpers::FileManager::ReadFile(
      directory_finder_.GetAbsPathOfTargetFile("img_2.jpg"));

  ASSERT_GT(image.size(), 0);
  EXPECT_TRUE(comparer_.LoadCache());

  // Expect to see a blank string
  std::chrono::time_point<std::chrono::system_clock> t1 =
      std::chrono::system_clock::now();
  std::string found_name = comparer_.FindImageInDirectory(image);
  std::chrono::time_point<std::chrono::system_clock> t2 =
      std::chrono::system_clock::now();

  EXPECT_TRUE(found_name.empty());

  std::chrono::microseconds duration =
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
  std::cout << "run time(us) " << duration.count() << std::endl;
}

}  // namespace image
