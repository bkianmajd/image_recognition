#include "libraries/protobuf_loader/protobuf_loader.h"

#include <iostream>

#include "gtest/gtest.h"
#include "libraries/protobuf_loader/cache_manager.h"
#include "schema/compiled_files/test_proto.pb.h"

namespace proto {
namespace {
constexpr int kTestInt = 5;
constexpr bool kTestBool = false;

}  // namespace

class ProtobufLoaderTest : public testing::Test {
 public:
  ProtobufLoaderTest()
      : directory_finder_(helpers::CreateDirectoryFinderFromWorkspace(
            "libraries/protobuf_loader/test")),
        loader_(directory_finder_.GetAbsPathOfTargetFile("test.pbtxt")) {}

 protected:
  helpers::DirectoryFinder directory_finder_;
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

TEST_F(ProtobufLoaderTest, CacheManagerTest) {
  {
    CacheManager<TestMap> map_(directory_finder_);
    // Reset
    map_.Reset();
    TestMap* test_map = map_.Get();
    ASSERT_TRUE(test_map);
    EXPECT_EQ(0, test_map->map1_size());

    // Store the buffer
    (*test_map->mutable_map1())[1] = "test";

    // destruct - unload binary
  }
  // Load the binary again
  CacheManager<TestMap> map_(directory_finder_);
  TestMap* test_map = map_.Get();
  ASSERT_TRUE(test_map);
  EXPECT_EQ(1, test_map->map1_size());
  EXPECT_EQ("test", test_map->map1().at(1));
}

}  // namespace proto
