#include "image_ipc/ipc_server/image_command_creator.h"

#include <iostream>

#include "gtest/gtest.h"
#include "schema/compiled_files/test_proto.pb.h"

namespace ipc {
namespace ipc_server {

class ImageCommandDistributorTest : public testing::Test {
 public:
  ImageCommandDistributorTest()
      : image_command_creator_(nullptr, &response_handler_) {}

 protected:
  postal_service::PostCardQueue response_handler_;
  ImageCommandCreator image_command_creator_;
};
TEST_F(ImageCommandDistributorTest, ConstructDestruct) {}

TEST_F(ImageCommandDistributorTest, CommandDistributor) {
  EXPECT_TRUE(response_handler_.Empty());
  TestProto proto;
  proto.set_test_bool(true);

  // pack this to an any
  google::protobuf::Any any;
  any.PackFrom(proto);

  image_command_creator_.Distribute(any);

  EXPECT_FALSE(response_handler_.Empty());
}

}  // namespace ipc_server
}  // namespace ipc
