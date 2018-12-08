#include "libraries/template_recognition/simple/simple_recognition.h"

#include <fstream>
#include <iostream>

#include "external_libraries/googletest/include/gtest/gtest.h"
#include "google_test/testing_def.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager/file_manager.h"
#include "libraries/template_recognition/template_recognition_interface.h"

namespace template_recognition {
namespace {

const std::string kFilePath = "template_recognition/simple/data/";
const int kTemplateInt = 1;

}  // namespace

class SimpleRecognitionTest : public testing::Test {
 public:
  SimpleRecognitionTest()
      : directory_finder_(
            tester::kTestingDirectoryFromWorkspace,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        kBigImg(directory_finder_.GetAbsPathOfTargetFile(
            tester::kBigImageChecker)),
        kTemplateImg(directory_finder_.GetAbsPathOfTargetFile(
            tester::kTemplateCheckers)) {}

 protected:
  helpers::DirectoryFinder directory_finder_;
  const std::string kBigImg;
  const std::string kTemplateImg;

  SimpleRecognition simple_recognition_;
};

TEST_F(SimpleRecognitionTest, ConstructDestruct) {
  TemplateRecognitionInterface* template_recognition = new SimpleRecognition();
  (void)template_recognition;
}

TEST_F(SimpleRecognitionTest, FileCheckTest) {
  std::ifstream test_open;
  test_open.open(kBigImg);
  EXPECT_TRUE(test_open.is_open());
  test_open.close();
  EXPECT_FALSE(test_open.is_open());
}

TEST_F(SimpleRecognitionTest, RegisterTest) {
  EXPECT_TRUE(simple_recognition_.RegisterImage(kTemplateImg));
  EXPECT_TRUE(simple_recognition_.RegisterImage(kBigImg));
  EXPECT_FALSE(simple_recognition_.RegisterImage(tester::kNoFile));
}

TEST_F(SimpleRecognitionTest, ImageRegisterTest) {
  EXPECT_TRUE(simple_recognition_.RegisterImage(kTemplateImg));
  EXPECT_TRUE(simple_recognition_.RegisterImage(kBigImg));
  EXPECT_FALSE(simple_recognition_.RegisterImage("no_file"));
}

TEST_F(SimpleRecognitionTest, TemplateStorageTest) {
  ASSERT_TRUE(simple_recognition_.RegisterTemplate(kTemplateInt, kTemplateImg));

  auto it = simple_recognition_.template_map_.find(kTemplateInt);
  EXPECT_TRUE(it != simple_recognition_.template_map_.end());

  cv::Mat templ = cv::imread(kTemplateImg, 1);
  EXPECT_EQ(it->second.cols, templ.cols);
}

TEST_F(SimpleRecognitionTest, GetTemplateMatchTest) {
  ASSERT_TRUE(simple_recognition_.RegisterImage(kBigImg));
  ASSERT_TRUE(simple_recognition_.RegisterTemplate(kTemplateInt, kTemplateImg));

  std::vector<Point> vector_point =
      simple_recognition_.GetTemplateMatch(kTemplateInt);
  Point& point = vector_point[1];
  EXPECT_TRUE(point.isValid);

  // predetermined from tutorial script
  EXPECT_EQ(point.x, 220);
  EXPECT_EQ(point.y, 61);
}

TEST_F(SimpleRecognitionTest, TemplateStorageTest2) {
  std::vector<char> bytes = helpers::FileManager::ReadFile(kBigImg);
  ASSERT_GT(static_cast<int>(bytes.size()), 0);

  ASSERT_TRUE(simple_recognition_.RegisterTemplate(kTemplateInt, bytes));

  auto it = simple_recognition_.template_map_.find(kTemplateInt);
  EXPECT_TRUE(it != simple_recognition_.template_map_.end());

  cv::Mat templ = cv::imread(kBigImg, 1);
  EXPECT_EQ(it->second.cols, templ.cols);
}

}  // namespace template_recognition
