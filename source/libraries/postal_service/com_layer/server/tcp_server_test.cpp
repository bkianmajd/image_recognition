#include "libraries/postal_service/com_layer/tcp_server.h"

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

TEST_F(TcpServerTest, SwapByteArrayTest) {
  tcp_server_.byte_read_array_.append("tcp_byte_array");

  std::string test_array = "test_array";

  tcp_server_.SwapReceivedByteArray(test_array);
  EXPECT_EQ("tcp_byte_array", test_array);
  EXPECT_NE("test_array", test_array);
  EXPECT_NE("tcp_byte_array", tcp_server_.byte_read_array_);
  EXPECT_EQ("test_array", tcp_server_.byte_read_array_);
}

}  // namespace rpc_server
