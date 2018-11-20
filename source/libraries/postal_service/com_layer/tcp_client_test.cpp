#include "libraries/postal_service/com_layer/tcp_client.h"

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

TEST_F(TcpClientTest, SwapByteArrayTest) {
  tcp_client_.byte_read_array_.append("tcp_byte_array");

  std::string test_array = "test_array";

  tcp_client_.SwapReceivedByteArray(test_array);
  EXPECT_EQ("tcp_byte_array", test_array);
  EXPECT_NE("test_array", test_array);
  EXPECT_NE("tcp_byte_array", tcp_client_.byte_read_array_);
  EXPECT_EQ("test_array", tcp_client_.byte_read_array_);
}

}  // namespace rpc_server
