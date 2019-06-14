#include "components/poker/statistics/brute_force_generator/table_generator_iterator.h"

#include <chrono>
#include <iostream>

#include "components/poker/statistics/brute_force_generator/table_generator.h"
#include "gtest/gtest.h"

namespace poker {
namespace statistics {
namespace {

std::vector<Card> GenerateExlusions() {
  std::vector<Card> exclusions;
  for (int i = 1; i <= 13; ++i) {
    exclusions.push_back(Card(static_cast<CardValue>(i), SUIT_SPADE));
  }
  for (int i = 1; i <= 13; ++i) {
    exclusions.push_back(Card(static_cast<CardValue>(i), SUIT_CLUB));
  }
  return exclusions;
}

}  // namespace

class TableGeneratorIteratorTest : public testing::Test {
 public:
  TableGeneratorIteratorTest()
      : table_generator_(GenerateExlusions()), tables_() {}
  ~TableGeneratorIteratorTest() = default;

 protected:
  TableGenerator table_generator_;
  std::vector<Table> tables_;
};

TEST_F(TableGeneratorIteratorTest, ExclusionTest) {
  tables_ = table_generator_.GenerateCombinations();

  std::vector<Card> exclusions = GenerateExlusions();
  for (int i = 1; i <= 13; ++i) {
    exclusions.push_back(Card(static_cast<CardValue>(i), SUIT_DIAMOND));
  }
  TableGeneratorIterator table_generator_iterator_(exclusions, tables_);

  // Expect combinations to equal = 13 * 12 * 11 * 10 * 9 / 5!
  constexpr int kExpectedCombo = 13 * 12 * 11 * 10 * 9 / (5 * 4 * 3 * 2);
  int counted_combos = 0;
  const Table* table;
  do {
    table = table_generator_iterator_.Next();
    if (table != nullptr) {
      counted_combos++;
    }
  } while (table != nullptr);

  EXPECT_EQ(kExpectedCombo, counted_combos);
}

TEST_F(TableGeneratorIteratorTest, ExpectedTest) {
  std::vector<Card> exclusions = GenerateExlusions();
  for (int i = 1; i <= 13; ++i) {
    exclusions.push_back(Card(static_cast<CardValue>(i), SUIT_DIAMOND));
  }
  TableGenerator generator(exclusions);
  tables_ = generator.GenerateCombinations();
  TableGeneratorIterator table_generator_iterator_(exclusions, tables_);

  // Expect combinations to equal = 13 * 12 * 11 * 10 * 9 / 5!
  constexpr int kExpectedCombo = 13 * 12 * 11 * 10 * 9 / (5 * 4 * 3 * 2);
  ASSERT_EQ(kExpectedCombo, tables_.size());

  int counted_combos = 0;
  const Table* table;
  do {
    table = table_generator_iterator_.Next();
    if (table != nullptr) {
      counted_combos++;
    }
  } while (table != nullptr);

  EXPECT_EQ(kExpectedCombo, counted_combos);
}

}  // namespace statistics
}  // namespace poker
