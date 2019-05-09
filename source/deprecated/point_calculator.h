#ifndef POINT_CALCULATOR_H_
#define POINT_CALCULATOR_H_

#include <algorithm>
#include <array>

#include "components/poker/entities/card_def.h"

namespace poker {
namespace simulator {

using Points = int;
using Hand = std::array<Card, 5>;

class PointCalculator {
 public:
  PointCalculator(const std::vector<Card>& unsorted_cards);

  Points GetPoints();

 private:
  // Finds the best 5 cards from the possible 7 cards
  // Brute force these combos - a total of 21 combos
  // 1 1 1 1 1 0 0 | 1 1 1 0 0 1 1
  // 1 1 1 1 0 0 1 | 1 1 0 0 1 1 1
  // 1 1 1 0 1 0 1 | 1 0 1 0 1 1 1
  // 1 1 0 1 1 0 1 | 0 1 1 0 1 1 1
  // 1 0 1 1 1 0 1 | 1 1 0 1 0 1 1
  // 0 1 1 1 1 0 1 | 1 0 1 1 0 1 1
  // 1 1 1 1 0 1 0 | 0 1 1 1 0 1 1
  // 1 1 1 0 1 1 0 | 1 0 0 1 1 1 1
  // 1 1 0 1 1 1 0 | 0 0 1 1 1 1 1
  // 1 0 1 1 1 1 0 | 0 1 0 1 1 1 1
  // 0 1 1 1 1 1 0 |
  Points GetMaximumPointsFrom7();

  Points GetPointsFrom5(const Hand& hand);

  const std::vector<Card> value_sorted_cards_;
};

}  // namespace simulator
}  // namespace poker

#endif  // POINT_CALCULATOR_H_
