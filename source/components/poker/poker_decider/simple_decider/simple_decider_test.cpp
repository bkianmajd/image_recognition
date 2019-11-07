#include "components/poker/poker_decider/simple_decider/simple_decider.h"

#include <iostream>

#include "gtest/gtest.h"

namespace poker {

class SimpleDeciderTest : public testing::Test {
 public:
  SimpleDeciderTest() {}

 protected:
  SimpleDecider simple_decider_;
};
TEST_F(SimpleDeciderTest, ConstructDestruct) {}

}  // namespace poker
