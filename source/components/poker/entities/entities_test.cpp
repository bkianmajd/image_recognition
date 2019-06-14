#include "components/poker/entities/card_def.h"

#include <iostream>
#include <unordered_map>

#include "gtest/gtest.h"

namespace poker {

class EntitiesTest : public testing::Test {
 public:
  EntitiesTest() = default;

  bool CheckForUnknown(const Card& card) {
    return card.suit == SUIT_UNKNOWN || card.value == CARD_VALUE_UNKNOWN;
  }

 protected:
};

TEST_F(EntitiesTest, UniqueIdTest) {
  for (CardId card_id = 0; card_id < 0xFF; ++card_id) {
    Card card = UniqueIdToCard(card_id);
    // ignore unknown fields - because the specific card id does not map to a
    // field
    if (CheckForUnknown(card)) {
      continue;
    }
    EXPECT_EQ(card_id, card.UniqueId());
  }
  Card card = UniqueIdToCard(0xFF);
  EXPECT_EQ(0xFF, card.UniqueId());
}

TEST_F(EntitiesTest, PlayerHandTest) {
  Card ace(CARD_VALUE_ACE, SUIT_CLUB);
  Card two(CARD_VALUE_TWO, SUIT_DIAMOND);

  CardsId id;
  id = CardToUniqueId(ace);
  id = id << 8;
  id = id + CardToUniqueId(two);
  // The first card should be two (lowest card)
  PlayerHand player_hand(id);
  EXPECT_EQ(player_hand.FirstCard(), two);
  EXPECT_EQ(player_hand.SecondCard(), ace);
  // Because these are already sorted, expect the unique id to equal
  EXPECT_EQ(id, player_hand.UniqueId());
}

TEST_F(EntitiesTest, TableTest) {
  Card ace(CARD_VALUE_ACE, SUIT_CLUB);
  Card two(CARD_VALUE_TWO, SUIT_DIAMOND);
  Card three(CARD_VALUE_THREE, SUIT_DIAMOND);
  Card four(CARD_VALUE_FOUR, SUIT_DIAMOND);
  Card five(CARD_VALUE_FIVE, SUIT_DIAMOND);

  CardsId id;
  // store from highest to lowest
  id = CardToUniqueId(ace);
  id = id << 8;
  id = id + CardToUniqueId(five);
  id = id << 8;
  id = id + CardToUniqueId(four);
  id = id << 8;
  id = id + CardToUniqueId(three);
  id = id << 8;
  id = id + CardToUniqueId(two);

  // The first card should be the lowest
  Table table(id);
  EXPECT_EQ(table.cards_[0], two);
  EXPECT_EQ(table.cards_[1], three);
  EXPECT_EQ(table.cards_[2], four);
  EXPECT_EQ(table.cards_[3], five);
  EXPECT_EQ(table.cards_[4], ace);

  // Because these are already sorted, expect the unique id to equal
  EXPECT_EQ(id, table.UniqueId());
}

TEST_F(EntitiesTest, CardComboTest) {
  Card ace(CARD_VALUE_ACE, SUIT_CLUB);
  Card two(CARD_VALUE_TWO, SUIT_DIAMOND);
  Card three(CARD_VALUE_THREE, SUIT_DIAMOND);
  Card four(CARD_VALUE_FOUR, SUIT_DIAMOND);
  Card five(CARD_VALUE_FIVE, SUIT_DIAMOND);
  Card six(CARD_VALUE_FIVE, SUIT_DIAMOND);
  Card seven(CARD_VALUE_FIVE, SUIT_DIAMOND);

  CardsId id;
  // store from highest to lowest
  id = CardToUniqueId(ace);
  id = id << 8;
  id = id + CardToUniqueId(seven);
  id = id << 8;
  id = id + CardToUniqueId(six);
  id = id << 8;
  id = id + CardToUniqueId(five);
  id = id << 8;
  id = id + CardToUniqueId(four);
  id = id << 8;
  id = id + CardToUniqueId(three);
  id = id << 8;
  id = id + CardToUniqueId(two);

  // The first card should be the lowest
  CardCombo card_combo(id);
  EXPECT_EQ(card_combo.cards_[0], two);
  EXPECT_EQ(card_combo.cards_[1], three);
  EXPECT_EQ(card_combo.cards_[2], four);
  EXPECT_EQ(card_combo.cards_[3], five);
  EXPECT_EQ(card_combo.cards_[4], six);
  EXPECT_EQ(card_combo.cards_[5], seven);
  EXPECT_EQ(card_combo.cards_[6], ace);

  // Because these are already sorted, expect the unique id to equal
  EXPECT_EQ(id, card_combo.UniqueId());
}

}  // namespace poker
