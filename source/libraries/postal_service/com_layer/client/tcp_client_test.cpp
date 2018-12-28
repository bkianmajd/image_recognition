#include "libraries/postal_service/com_layer/client/tcp_client.h"

#include <fstream>
#include <iostream>

#include "external_libraries/googletest/include/gtest/gtest.h"
#include "google_test/testing_def.h"

namespace com_layer {

namespace {}  // namespace

class TcpClientTest : public testing::Test {
 public:
  TcpClientTest() {}

 protected:
  TcpClient tcp_client_;
};

TEST_F(TcpClientTest, ConstructDestruct) {}

}  // namespace rpc_server
