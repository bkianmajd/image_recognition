#include "com_layer/tcp_server.h"

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

TEST_F(TcpServerTest, WriteToFile) {

}

}  // namespace rpc_server
