#include "components/poker/statistics/winning_calculator/winning_calculator.h"
#include "helpers/time_analyzer.h"

#include <iostream>

#include "gtest/gtest.h"

// This will populate the test. This takes a long time to complete

namespace poker {
namespace statistics {
namespace {

constexpr int kOpponents = 1;
constexpr bool kReset = false;

const std::string kCacheDir =
    "components/poker/statistics/cache_manager/binary_data";
const std::string kPreflopCache = "genericPreflop.dat";
const std::string kPostflopCache = "genericPostflop.dat";

}  // namespace

// Reduces the 2 card input
class FeatureReduction {

};

class CacheStorageTest : public testing::Test {
 public:
  CacheStorageTest()
      : cache_manager_(std::make_unique<CacheManager>(
            helpers::CreateDirectoryFinderFromWorkspace(kCacheDir),
            kPreflopCache, kPostflopCache)),
        winning_calculator_(cache_manager_.get()) {
    if (kReset) {
      cache_manager_->Reset();
    }
    cache_manager_->InitializeLoad();
  }

 protected:
  std::unique_ptr<CacheManager> cache_manager_;
  WinningCalculator winning_calculator_;
};

// Populates all combinations for preflop in the cache manager binaries
TEST_F(CacheStorageTest, PreflopTest) {
  // Generate all possible combinations for a hand with no exclusions
  std::vector<Card> no_exclusions;
  HandGenerator hand_generator(no_exclusions);
  std::vector<PlayerHand> player_hands = hand_generator.GenerateCombinations();

  std::cout << "Generating combinations for " << player_hands.size()
            << " combinations." << std::endl;

  std::vector<Card> empty_table;
  for (const PlayerHand& player_hand : player_hands) {
    std::cout << "Calculating hand: " << player_hand.FirstCard() << " "
              << player_hand.SecondCard() << std::endl;

    TIME_ANALYZE(winning_calculator_.GetWinningProbability(player_hand, empty_table,
                                                           kOpponents))
  }
  EXPECT_GT(cache_manager_->preflop_map_.size(), 0);
  cache_manager_->ShutdownStore();
}

}  // namespace statistics
}  // namespace poker
