#include "components/poker/entities/card_def.h"

#include <iostream>

#include "gtest/gtest.h"

namespace poker {

class EntitiesTest : public testing::Test {
 public:
  EntitiesTest() = default;

 protected:
};
TEST_F(EntitiesTest, UniqueIdTest) {
  Card card1(CARD_VALUE_ACE, SUIT_SPADE);
  Card card2(CARD_VALUE_TWO, SUIT_SPADE);
  Card card14(CARD_VALUE_ACE, SUIT_CLUB);
  Card card27(CARD_VALUE_ACE, SUIT_DIAMOND);
  Card card40(CARD_VALUE_ACE, SUIT_HEART);
  Card card52(CARD_VALUE_KING, SUIT_HEART);

  EXPECT_EQ(1, CardToUniqueId(card1));
  EXPECT_EQ(2, CardToUniqueId(card2));
  EXPECT_EQ(14, CardToUniqueId(card14));
  EXPECT_EQ(27, CardToUniqueId(card27));
  EXPECT_EQ(40, CardToUniqueId(card40));
  EXPECT_EQ(52, CardToUniqueId(card52));

  // Testing uniqueId to Card
  EXPECT_EQ(card1, UniqueIdToCard(1));
  EXPECT_EQ(card2, UniqueIdToCard(2));
  EXPECT_EQ(card14, UniqueIdToCard(14));
  EXPECT_EQ(card27, UniqueIdToCard(27));
  EXPECT_EQ(card40, UniqueIdToCard(40));
  EXPECT_EQ(card52, UniqueIdToCard(52));
}

}  // namespace simulator_defs
