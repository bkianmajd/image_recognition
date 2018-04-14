#include "image_ipc/ipc_server/ipc_server.h"

#include <iostream>
#include <fstream>

#include "google_test/testing_def.h"
#include "external_libraries/googletest/include/gtest/gtest.h"

namespace ipc_server {

namespace {


}  // namespace

class IpcServerTest : public testing::Test {
public:
  IpcServerTest() {}

protected:
    IpcServer ipc_server_;

};

TEST_F(IpcServerTest, ConstructDestruct) {
}

TEST_F(IpcServerTest, SendImageTest) {

}

}  // namespace rpc_server
