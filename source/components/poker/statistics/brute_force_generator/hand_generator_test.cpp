#include "components/poker/statistics/brute_force_generator/hand_generator.h"

#include <iostream>
#include <unordered_set>

#include "gtest/gtest.h"

namespace poker {
namespace statistics {
namespace {

// n! / (r! * (n-r)!)
// 50*49 / 2
constexpr int kExpectedRuns = 1225;

std::vector<Card> GenerateExlusions() {
  std::vector<Card> exclusions;
  exclusions.push_back(Card(CARD_VALUE_ACE, SUIT_SPADE));
  exclusions.push_back(Card(CARD_VALUE_ACE, SUIT_HEART));
  return exclusions;
}
}  // namespace

class HandGeneratorTest : public testing::Test {
 public:
  HandGeneratorTest() : hand_generator_(GenerateExlusions()) {}
  ~HandGeneratorTest() = default;

 protected:
  HandGenerator hand_generator_;
};
TEST_F(HandGeneratorTest, ConstructDestruct) {}

TEST_F(HandGeneratorTest, CombinationTest) {
  std::vector<PlayerHand> combinations = hand_generator_.GenerateCombinations();
  EXPECT_EQ(kExpectedRuns, static_cast<int>(combinations.size()));
  // Test for duplications
  std::unordered_set<int> set;
  for (const PlayerHand& hand : combinations) {
    int first_card = CardToUniqueId(hand.FirstCard());
    int second_card = CardToUniqueId(hand.SecondCard());
    // Shift the first card by 2 digits to the left
    int key = first_card * 1000 + second_card;
    auto it = set.find(key);
    if (it != set.end()) {
      FAIL();
    }
  }
}

}  // namespace statistics
}  // namespace poker
