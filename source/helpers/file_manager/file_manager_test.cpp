#include "helpers/file_manager/file_manager.h"

#include <QFile>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "google_test/testing_def.h"
#include "gtest/gtest.h"
#include "helpers/directory_finder.h"
#include "helpers/memory_helper.hpp"

namespace helpers {
namespace {
const std::string kTestImage = "test_output.jpg";
}  // namespace

class FileManagerTest : public testing::Test {
 public:
  FileManagerTest()
      : directory_(
            tester::kTestingDirectoryFromWorkspace,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace) {}

 protected:
  helpers::DirectoryFinder directory_;
};
TEST_F(FileManagerTest, ConstructDestruct) {}

TEST_F(FileManagerTest, ReadSaveAndDeleteImage) {
  std::vector<char> binary_data = FileManager::ReadFile(
      directory_.GetAbsPathOfTargetFile(tester::kTemplateCheckers));
  ASSERT_GT(binary_data.size(), static_cast<unsigned int>(0));

  ASSERT_TRUE(FileManager::StoreFile(binary_data.data(), binary_data.size(),
                                     kTestImage));

  // Atempt to delete the imaeg
  EXPECT_TRUE(FileManager::DeleteFile(kTestImage));
}

}  // namespace helpers
