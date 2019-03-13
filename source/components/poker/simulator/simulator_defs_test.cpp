#include "components/poker/simulator/deck_stack_factory.h"

#include <iostream>

#include "gtest/gtest.h"

namespace poker {
namespace {
constexpr int kDeckSize = 52;
}

class SimulatorDefsTest : public testing::Test {
 public:
  SimulatorDefsTest() : deck_stack_factory_() {}

 protected:
  DeckStackFactory deck_stack_factory_;
};
TEST_F(SimulatorDefsTest, ConstructDestruct) {}

TEST_F(SimulatorDefsTest, InitialDeckTest) {
  std::stack<Card> deck = deck_stack_factory_.CreateSimpleStack();
  EXPECT_EQ(kDeckSize, deck.size());
}

}  // namespace poker
