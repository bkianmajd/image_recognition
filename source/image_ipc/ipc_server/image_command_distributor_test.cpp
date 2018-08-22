#include "image_ipc/ipc_server/image_command_distributor.h"

#include <iostream>

#include "gtest/gtest.h"
#include "image_ipc/ipc_server/image_command_distributor.h"
#include "schema/compiled_files/test_proto.pb.cc"

namespace ipc {
namespace ipc_server {

class ImageCommandDistributorTest : public testing::Test {
 public:
  ImageCommandDistributorTest()
      : image_command_distributor_(nullptr, &response_handler_) {}

 protected:
  ResponseHandler response_handler_;
  ImageCommandDistributor image_command_distributor_;
};
TEST_F(ImageCommandDistributorTest, ConstructDestruct) {}

TEST_F(ImageCommandDistributorTest, CommandDistributor) {
  EXPECT_TRUE(response_handler_.Empty());
  TestProto proto;
  proto.set_test_bool(true);

  // pack this to an any
  google::protobuf::Any any;
  any.PackFrom(proto);

  image_command_distributor_.Distribute(any);

  EXPECT_FALSE(response_handler_.Empty());
}

}  // namespace ipc_server
}  // namespace ipc
