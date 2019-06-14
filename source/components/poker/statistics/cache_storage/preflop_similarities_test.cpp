#include "components/poker/statistics/cache_storage/preflop_similarities.h"

#include "helpers/time_analyzer.h"

#include "base/bind.h"
#include "base/callback.h"
#include "gtest/gtest.h"

#include <iostream>

namespace poker {
namespace statistics {

class PreflopSimilaritiesTest : public testing::Test {
 public:
  PreflopSimilaritiesTest() = default;

 protected:
  PreflopSimilarities similar_checker_;
};
TEST_F(PreflopSimilaritiesTest, ConstructDestruct) {}

TEST_F(PreflopSimilaritiesTest, CleanseTest) {
  PlayerHand hand_to_cleanse(Card(CARD_VALUE_ACE, SUIT_HEART),
                             Card(CARD_VALUE_ACE, SUIT_CLUB));

  std::vector<PlayerHand> player_hands;
  player_hands.push_back(hand_to_cleanse);
  player_hands.emplace_back(Card(CARD_VALUE_ACE, SUIT_CLUB),
                            Card(CARD_VALUE_ACE, SUIT_HEART));
  player_hands.emplace_back(Card(CARD_VALUE_ACE, SUIT_CLUB),
                            Card(CARD_VALUE_ACE, SUIT_SPADE));

  EXPECT_EQ(3, player_hands.size());
  similar_checker_.Cleanse(hand_to_cleanse, &player_hands);
  EXPECT_EQ(1, player_hands.size());
}

TEST_F(PreflopSimilaritiesTest, SimilarTest) {
  PlayerHand pocket_aces(Card(CARD_VALUE_ACE, SUIT_HEART),
                         Card(CARD_VALUE_ACE, SUIT_CLUB));
  std::vector<PlayerHand> similar_hands =
      similar_checker_.GetSimilarities(pocket_aces);

  // make sure the original pocket aces are not in similar_hands
  for (const PlayerHand& player_hand : similar_hands) {
    ASSERT_FALSE(player_hand.UniqueId() == pocket_aces.UniqueId());
    ASSERT_TRUE(player_hand.FirstCard().value == CARD_VALUE_ACE);
    ASSERT_TRUE(player_hand.SecondCard().value == CARD_VALUE_ACE);
    ASSERT_TRUE(player_hand.FirstCard().suit != player_hand.SecondCard().suit);
  }
}

TEST_F(PreflopSimilaritiesTest, CleanseUniqueIdTest) {
  std::vector<PlayerHand> similar_hands;
  similar_hands.emplace_back(Card(CARD_VALUE_ACE, SUIT_HEART),
                             Card(CARD_VALUE_ACE, SUIT_CLUB));
  similar_hands.emplace_back(Card(CARD_VALUE_ACE, SUIT_CLUB),
                             Card(CARD_VALUE_ACE, SUIT_HEART));
  similar_hands.emplace_back(Card(CARD_VALUE_ACE, SUIT_SPADE),
                             Card(CARD_VALUE_ACE, SUIT_HEART));
  similar_hands.emplace_back(Card(CARD_VALUE_ACE, SUIT_HEART),
                             Card(CARD_VALUE_ACE, SUIT_CLUB));

  // There is only 2 unique hands
  similar_checker_.CleanseUniqueId(&similar_hands);
  EXPECT_EQ(2, similar_hands.size());
}

}  // namespace statistics
}  // namespace poker
