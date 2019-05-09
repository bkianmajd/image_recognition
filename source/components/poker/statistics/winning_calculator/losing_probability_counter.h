#ifndef LOSING_PROBABILITY_COUNTER_H_
#define LOSING_PROBABILITY_COUNTER_H_

#include <cassert>
#include <vector>

#include "components/poker/entities/card_def.h"

namespace poker {
namespace statistics {

// Counts all the losses and wins
class LosingProbabilityCounter {
  void AddDataPoint(const PlayerHand& player_hand,
                    const PlayerHand& opponent_hand,
                    const std::vector<Card>& table) {
    assert(table.size() == 5);


  }

  double CalculateLosingProbability() const {
    if (total_size_ == 0) {
      return 0;
    }
    return static_cast<double>(win_counter_) / static_cast<double>(total_size_);
  }

 private:
  int win_counter_;
  int total_size_;
};

}  // namespace statistics
}  // namespace poker

#endif  // LOSING_PROBABILITY_COUNTER_H_
