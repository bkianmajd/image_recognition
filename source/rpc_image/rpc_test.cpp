#include "rpc_image/rpc_server/rpc_server.h"

#include <iostream>
#include <fstream>

#include "google_test/testing_def.h"
#include "external_libraries/googletest/include/gtest/gtest.h"

namespace rpc_server {

namespace {


}  // namespace

class RpcTest : public testing::Test {
public:
  RpcTest() {}

protected:
    RpcServer rpc_server_;

};

TEST_F(RpcTest, ConstructDestruct) {
}

TEST_F(RpcTest, SendImageTest) {

}

}  // namespace rpc_server
