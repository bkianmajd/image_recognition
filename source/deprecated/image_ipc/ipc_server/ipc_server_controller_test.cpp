#include "image_ipc/ipc_server/ipc_server_controller.h"

#include <iostream>
#include "gtest/gtest.h"

namespace ipc {
namespace ipc_server {

// We don't employ mocks, so can only do trivial testing in this class.
class IpcServerControllerTest : public testing::Test {
 public:
  IpcServerControllerTest() : controller_(nullptr, nullptr, nullptr) {}

 protected:
  IpcServerController controller_;
};
TEST_F(IpcServerControllerTest, ConstructDestruct) {}

TEST_F(IpcServerControllerTest, TimeoutInitializeTest) {
  controller_.Initialize();
}

}  // namespace ipc_server
}  // namespace ipc
