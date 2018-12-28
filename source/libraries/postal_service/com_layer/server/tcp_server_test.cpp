#include "libraries/postal_service/com_layer/server/tcp_server.h"

#include <iostream>
#include <fstream>

#include "google_test/testing_def.h"
#include "external_libraries/googletest/include/gtest/gtest.h"

namespace com_layer {
namespace {


}  // namespace

class TcpServerTest : public testing::Test {
public:
  TcpServerTest() {}

protected:
    TcpServer tcp_server_;

};

TEST_F(TcpServerTest, ConstructDestruct) {
}

}  // namespace rpc_server
