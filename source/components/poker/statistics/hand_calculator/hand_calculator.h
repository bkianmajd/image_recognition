#ifndef WINNING_CALCULATOR_H_
#define WINNING_CALCULATOR_H_

#include <gtest/gtest_prod.h>

#include "components/poker/entities/card_def.h"
#include "components/poker/statistics/defs/defs.h"
#include "libraries/protobuf_loader/cache_manager.h"

#include "components/poker/statistics/cache_storage/proto/poker_statistics.pb.h"

#include "base/optional.h"

namespace poker {
namespace statistics {

/// Calculates the probability given a players hand
class HandCalculator {
 public:
  HandCalculator();

  HandStatistic CalculateHandProbability(const PlayerHand& player_hand,
                                         const Table& table, int opponents);

 private:
  HandStatistic GetHandStatisticPreFlop(const PlayerHand& player_hand);

  proto::CacheManager<poker::PreFlopStatistic> cache_manager_;
};

}  // namespace statistics
}  // namespace poker

#endif  // WINNING_CALCULATOR_H_
