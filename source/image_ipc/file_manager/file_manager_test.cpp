#include "image_ipc/file_manager/file_manager.h"

#include <QFile>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"
#include "helpers/directory_finder.h"
#include "helpers/memory_helper.hpp"

namespace ipc {
namespace ipc_server {

namespace {
const std::string kDirectoryInWorkspace = "data/test/";
const std::string kSrcImage = "test.jpg";
const std::string kTestImage = "test_output.jpg";
}  // namespace

std::string GetTestFolderInWorkspace() {
  helpers::DirectoryFinder workspace(kDirectoryInWorkspace);
  return workspace.GetAbsPathRelativeToWorkspace();
}

class FileManagerTest : public testing::Test {
 public:
  FileManagerTest() : file_manager_(GetTestFolderInWorkspace()) {}

 protected:
  FileManager file_manager_;
};
TEST_F(FileManagerTest, ConstructDestruct) {}

TEST_F(FileManagerTest, ReadSaveAndDeleteImage) {
  std::vector<char> binary_data = file_manager_.ReadFile(kSrcImage);
  ASSERT_GT(binary_data.size(), static_cast<unsigned int>(0));

  ASSERT_TRUE(file_manager_.StoreFile(binary_data.data(), binary_data.size(),
                                      kTestImage));

  // Atempt to delete the imaeg
  EXPECT_TRUE(file_manager_.DeleteFile(kTestImage));
}

}  // namespace ipc_server
}  // namespace ipc
