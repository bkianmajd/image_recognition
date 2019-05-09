#include "components/poker/statistics/cache_manager/cache_manager.h"

#include <iostream>
#include <unordered_set>

#include "gtest/gtest.h"

namespace poker {
namespace statistics {
namespace {

const std::string kBinaryDir =
    "components/poker/statistics/cache_manager/binary_data";
const std::string kPreFlopTestData = "preflop_test.dat";
const std::string kPostFlopTestData = "postflop_test.dat";

constexpr double kTestProb = .001;

}  // namespace
class CacheManagerTest : public testing::Test {
 public:
  CacheManagerTest()
      : cache_manager_(helpers::CreateDirectoryFinderFromWorkspace(kBinaryDir),
                       kPreFlopTestData, kPostFlopTestData),
        preflop_loader_(helpers::CreateDirectoryFinderFromWorkspace(kBinaryDir),
                        kPreFlopTestData),
        postflop_loader_(
            helpers::CreateDirectoryFinderFromWorkspace(kBinaryDir),
            kPostFlopTestData) {}

 protected:
  CacheManager cache_manager_;
  proto::ProtobufLoader preflop_loader_;
  proto::ProtobufLoader postflop_loader_;
};

TEST_F(CacheManagerTest, ConstructDestruct) {}

TEST_F(CacheManagerTest, ShutdownTest) {
  EXPECT_FALSE(cache_manager_.initialized_);
  // manually initialize
  cache_manager_.initialized_ = true;

  cache_manager_.preflop_map_[1] = kTestProb;
  cache_manager_.postflop_map_[1] = kTestProb;
  cache_manager_.postflop_map_[2] = kTestProb;
  cache_manager_.ShutdownStore();

  PreflopStatistics preflop_statistics;
  ASSERT_TRUE(preflop_loader_.LoadProtobuf(&preflop_statistics));
  ASSERT_EQ(1, preflop_statistics.preflop_statistics_size());

  EXPECT_EQ(
      kTestProb,
      preflop_statistics.mutable_preflop_statistics(0)->losing_probability());

  // Testing post flop statistics
  PostFlopStatistics postflop_statistics;
  ASSERT_TRUE(postflop_loader_.LoadProtobuf(&postflop_statistics));
  ASSERT_EQ(2, postflop_statistics.post_flop_statistics_size());
  EXPECT_EQ(kTestProb, postflop_statistics.mutable_post_flop_statistics(0)
                           ->losing_probability());
  EXPECT_EQ(kTestProb, postflop_statistics.mutable_post_flop_statistics(1)
                           ->losing_probability());
}

TEST_F(CacheManagerTest, LoadTest) {
  EXPECT_FALSE(cache_manager_.initialized_);
  constexpr int k_preSize = 3;
  constexpr int k_postSize = 5;

  // Manually store the dat file up to 3 times
  PreflopStatistics preflop_statistics;
  for (int i = 0; i < 3; ++i) {
    PreFlopStatistic* stat = preflop_statistics.add_preflop_statistics();
    stat->set_hand_sorted_id(i);
    stat->set_losing_probability(kTestProb);
  }
  preflop_loader_.StoreProtobuf(preflop_statistics);

  // Manually store the dat file up to 5 times here
  PostFlopStatistics postflop_statistics;
  for (int i = 0; i < k_postSize; ++i) {
    PostFlopStatistic* stat = postflop_statistics.add_post_flop_statistics();
    stat->set_hand_table_unique_id(i);
    stat->set_losing_probability(kTestProb);
  }
  postflop_loader_.StoreProtobuf(postflop_statistics);

  // Load the data
  cache_manager_.InitializeLoad();

  // Test to see if the data was loaded in the map
  EXPECT_EQ(k_preSize, cache_manager_.preflop_map_.size());
  EXPECT_EQ(k_postSize, cache_manager_.postflop_map_.size());

  for (int i = 0; i < k_preSize; ++i) {
    cache_manager_.preflop_map_[i] = kTestProb;
    cache_manager_.postflop_map_[i] = kTestProb;
  }
}

}  // namespace statistics
}  // namespace poker
