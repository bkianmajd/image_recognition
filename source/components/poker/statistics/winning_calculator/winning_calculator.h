#ifndef WINNING_CALCULATOR_H_
#define WINNING_CALCULATOR_H_

#include "components/poker/statistics/brute_force_generator/table_generator.h"
#include "components/poker/statistics/brute_force_generator/hand_generator.h"
#include "components/poker/entities/card_def.h"

namespace poker {
namespace statistics {

/// Calculates the probability given a players hand
class WinningCalculator {
 public:
  WinningCalculator(const PlayerHand& player_hand);

  double GetWinningProbability(Table table, int oponents);

 private:
  // protobuf reader
};

}  // namespace statistics
}  // namespace poker

#endif  // WINNING_CALCULATOR_H_
