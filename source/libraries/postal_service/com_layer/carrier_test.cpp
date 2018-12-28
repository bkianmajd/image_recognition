#include "libraries/postal_service/com_layer/carrier_base.h"

#include <fstream>
#include <iostream>
#include <memory>

#include "external_libraries/googletest/include/gtest/gtest.h"
#include "google_test/testing_def.h"
#include "libraries/postal_service/com_layer/carrier_mock.h"

namespace com_layer {
namespace {}  // namespace

class CarrierTest : public testing::Test {
 public:
  CarrierTest() : carrier_base_(std::make_unique<CarrierMock>()) {}
  ~CarrierTest() = default;

  void TcpRead(const std::string& str) {
    carrier_base_->ProcessReadBytes(str.c_str());
  }

 protected:
  std::unique_ptr<CarrierBase> carrier_base_;
};

TEST_F(CarrierTest, ConstructDestruct) {}

TEST_F(CarrierTest, ReadByteArrayTest) {
  TcpRead("test");
  std::string test = carrier_base_->ReadByteArray();

  // There should be nothing in here because the end packet was not read
  EXPECT_TRUE(test.empty());

  TcpRead(carrier_base_->kEndPacket);
  test = carrier_base_->ReadByteArray();
  EXPECT_EQ(test, "test");
}

}  // namespace rpc_server
