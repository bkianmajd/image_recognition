#include "components/poker/statistics/brute_force_generator/table_generator.h"

#include <chrono>
#include <iostream>

#include "gtest/gtest.h"

namespace poker {
namespace statistics {
namespace {

// n! / (r! * (n-r)!)
// 48 * 47 * 46 * 45 * 44/(5 * 4 * 3 * 2)
constexpr int kExpectedPreFlopRuns = 1712304;
constexpr int kExpectedPostFlopRuns = 990;
constexpr int kExpectedPostTurnRuns = 44;

std::vector<Card> GenerateExlusions() {
  std::vector<Card> exclusions;
  exclusions.push_back(Card(CARD_VALUE_ACE, SUIT_SPADE));
  exclusions.push_back(Card(CARD_VALUE_ACE, SUIT_CLUB));
  exclusions.push_back(Card(CARD_VALUE_ACE, SUIT_DIAMOND));
  exclusions.push_back(Card(CARD_VALUE_ACE, SUIT_HEART));
  return exclusions;
}
}  // namespace

class TableGeneratorTest : public testing::Test {
 public:
  TableGeneratorTest() : table_generator_(GenerateExlusions()) {}
  ~TableGeneratorTest() = default;

 protected:
  TableGenerator table_generator_;
};
TEST_F(TableGeneratorTest, ConstructDestruct) {}

TEST_F(TableGeneratorTest, FlopTest) {
  std::vector<Table> combinations = table_generator_.GenerateCombinations();
  EXPECT_EQ(kExpectedPreFlopRuns, static_cast<int>(combinations.size()));
}

TEST_F(TableGeneratorTest, TurnTest) {
  Card first_card = Card(CARD_VALUE_TWO, SUIT_SPADE);
  Card second_card = Card(CARD_VALUE_TWO, SUIT_CLUB);
  Card third_card = Card(CARD_VALUE_TWO, SUIT_DIAMOND);

  // time this
  std::chrono::time_point<std::chrono::system_clock> t1 =
      std::chrono::system_clock::now();
  std::vector<Table> combinations = table_generator_.GenerateCombinations(
      first_card, second_card, third_card);
  std::chrono::time_point<std::chrono::system_clock> t2 =
      std::chrono::system_clock::now();

  EXPECT_EQ(kExpectedPostFlopRuns, static_cast<int>(combinations.size()));

  std::chrono::microseconds diff =
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
  std::cout << "microseconds: " << diff.count() << std::endl;
}

TEST_F(TableGeneratorTest, RiverTest) {
  Card first_card = Card(CARD_VALUE_TWO, SUIT_SPADE);
  Card second_card = Card(CARD_VALUE_TWO, SUIT_CLUB);
  Card third_card = Card(CARD_VALUE_TWO, SUIT_DIAMOND);
  Card fourth_card = Card(CARD_VALUE_TWO, SUIT_HEART);

  // time this
  std::chrono::time_point<std::chrono::system_clock> t1 =
      std::chrono::system_clock::now();
  std::vector<Table> combinations = table_generator_.GenerateCombinations(
      first_card, second_card, third_card, fourth_card);
  std::chrono::time_point<std::chrono::system_clock> t2 =
      std::chrono::system_clock::now();

  EXPECT_EQ(kExpectedPostTurnRuns, static_cast<int>(combinations.size()));

  std::chrono::microseconds diff =
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
  std::cout << "microseconds: " << diff.count() << std::endl;
}

}  // namespace statistics
}  // namespace poker
