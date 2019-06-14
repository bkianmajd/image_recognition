#ifndef TABLE_GENERATOR_ITERATOR_H_
#define TABLE_GENERATOR_ITERATOR_H_

#include <array>
#include <vector>

#include "components/poker/entities/card_def.h"
#include "components/poker/simulator/deck_stack_factory.h"
#include "components/poker/statistics/brute_force_generator/hand_generator.h"

namespace poker {
namespace statistics {

/// Generates all the card possibilities on a table for a given pair of hands,
/// and oponents hands
class TableGeneratorIterator {
 public:
  explicit TableGeneratorIterator(const std::vector<Card>& exclusions, const std::vector<Table>& table);

  /// Verifies and calls next. returns nullptr if at end
  const Table* Next();

  void Reset();

 private:
  bool Verify() const;

  std::vector<Card> exclusions_;
  const std::vector<Table>& tables_;
  uint64_t index_;
};

}  // namespace statistics
}  // namespace poker

#endif  // TABLE_GENERATOR_ITERATOR_H_
