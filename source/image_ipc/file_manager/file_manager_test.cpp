#include "image_ipc/file_manager/file_manager.h"

#include <iostream>
#include "gtest/gtest.h"

namespace ipc {
namespace ipc_server {

namespace {
const char* kTestImage = "data/test/test_image.jpg";
}

class FileManagerTest : public testing::Test {
 public:
  FileManagerTest() : file_manager_("") {}

 protected:
  FileManager file_manager_;
};
TEST_F(FileManagerTest, ConstructDestruct) {}

TEST_F(FileManagerTest, SaveImage) {
  uchar* test;
  file_manager_.StoreImage(test, 0, kTestImage);
}

}  // namespace ipc_server
}  // namespace ipc
