#include "libraries/protobuf_loader/protobuf_loader.h"

#include <iostream>

#include "gtest/gtest.h"
#include "schema/compiled_files/test_proto.pb.h"

namespace proto {
namespace {
constexpr int kTestInt = 5;
constexpr bool kTestBool = false;
}  // namespace

class ProtobufLoaderTest : public testing::Test {
 public:
  ProtobufLoaderTest()
      : loader_(helpers::CreateDirectoryFinderFromWorkspace(
                    "libraries/protobuf_loader/test"),
                "test.pbtxt") {}

 protected:
  ProtobufLoader loader_;
};

TEST_F(ProtobufLoaderTest, ConstructDestruct) {}

TEST_F(ProtobufLoaderTest, StoreTest) {
  TestProto test_proto;
  test_proto.set_test_int(kTestInt);
  test_proto.set_test_bool(kTestBool);

  EXPECT_TRUE(loader_.StoreProtobuf(test_proto));

  TestProto loaded_proto;
  EXPECT_TRUE(loader_.LoadProtobuf(&loaded_proto));

  EXPECT_EQ(kTestInt, loaded_proto.test_int());
  EXPECT_EQ(kTestBool, loaded_proto.test_bool());
}

}  // namespace proto
