#include "components/poker/statistics/cache_storage/cache_worker.h"

#include "helpers/time_analyzer.h"

#include "base/bind.h"
#include "base/callback.h"
#include "gtest/gtest.h"

#include <iostream>

namespace poker {
namespace statistics {

class CacheStorageTest : public testing::Test {
 public:
  CacheStorageTest()
      : player_hand_(Card(CARD_VALUE_TWO, SUIT_CLUB),
                     Card(CARD_VALUE_TWO, SUIT_HEART)),
        opponent_hand1_(Card(CARD_VALUE_ACE, SUIT_SPADE),
                        Card(CARD_VALUE_KING, SUIT_CLUB)),
        opponent_hand2_(Card(CARD_VALUE_ACE, SUIT_SPADE),
                        Card(CARD_VALUE_NINE, SUIT_CLUB)) {
    exclusions_.push_back(player_hand_.FirstCard());
    exclusions_.push_back(player_hand_.SecondCard());
  }

  void OnWorkerComplete(const WorkerResponse& worker_response) {
    EXPECT_GT(worker_response.losing_probability, 0);

    if (worker_response.opponent_hand.SecondCard() ==
        opponent_hand1_.SecondCard()) {
      losing_probability1_ = worker_response.losing_probability;
      return;
    }
    losing_probability2_ = worker_response.losing_probability;
  }

 protected:
  PlayerHand player_hand_;
  PlayerHand opponent_hand1_;
  PlayerHand opponent_hand2_;
  std::vector<Card> exclusions_;

  double losing_probability1_;
  double losing_probability2_;
};
TEST_F(CacheStorageTest, CacheStorageWorkerTest) {
  base::MessageLoop message_loop;
  base::RunLoop run_loop;

  // Generate table combinations
  helpers::TimeAnalyzer analyze_combo_gen;
  TableGenerator table_gen(exclusions_);
  std::vector<Table> table_combos = table_gen.GenerateCombinations();
  analyze_combo_gen.Debug("Generate combinations: ");

  // Run first calculation for opponent hand 1
  helpers::TimeAnalyzer time_analyze;
  auto dispatcher_callback =
      base::Bind(&CacheStorageTest::OnWorkerComplete, base::Unretained(this));
  CacheWorker cache_worker(table_combos, message_loop.task_runner(),
                           dispatcher_callback);

  cache_worker.Calculate(player_hand_, opponent_hand1_);
  time_analyze.Debug("Cache worker.calculate ");

  // run second calculation for opponent hand 2
  helpers::TimeAnalyzer time_analyze2;
  cache_worker.Calculate(player_hand_, opponent_hand2_);
  time_analyze2.Debug("Second calculation: ");

  run_loop.RunUntilIdle();
  std::cout << "Losing probability1: " << losing_probability1_ << std::endl;
  std::cout << "Losing probability2: " << losing_probability2_ << std::endl;

  // Expect 22 to have a higher losing probability to AK than Ace Nine
  EXPECT_GT(losing_probability1_, losing_probability2_);
}

}  // namespace statistics
}  // namespace poker
