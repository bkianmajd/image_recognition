#include "components/poker/statistics/brute_force_generator/table_generator_iterator.h"

#include <array>
#include <vector>

#include "components/poker/entities/card_def.h"
#include "components/poker/simulator/deck_stack_factory.h"
#include "components/poker/statistics/brute_force_generator/hand_generator.h"

namespace poker {
namespace statistics {

TableGeneratorIterator::TableGeneratorIterator(
    const std::vector<Card>& exclusions, const std::vector<Table>& tables)
    : exclusions_(exclusions), tables_(tables), index_(0) {}

void TableGeneratorIterator::Reset() { index_ = 0; }

const Table* TableGeneratorIterator::Next() {
  if (index_ == tables_.size()) {
    return nullptr;
  }

  if (index_ == 0 && Verify()) {
    index_++;
    return &tables_[0];
  }

  while (!Verify()) {
    index_++;
    if (index_ == tables_.size()) {
      return nullptr;
    }
  }

  return &tables_[index_++];
}

bool TableGeneratorIterator::Verify() const {
  const Table& table = tables_[index_];
  // return false when you find an exclusion
  for (const Card& card : exclusions_) {
    for (size_t i = 0; i < 5; ++i) {
      if (table.cards_[i] == card) {
        return false;
      }
    }
  }

  return true;
}

}  // namespace statistics
}  // namespace poker
