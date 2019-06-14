#include "components/poker/poker_game_controller/sanity_check/sanity_checker.h"

#include <iostream>

#include "gtest/gtest.h"

namespace poker {
namespace {
const Card kUnknownCard;
const Card kAceClub(CARD_VALUE_ACE, SUIT_CLUB);
const Card kAceHeart(CARD_VALUE_ACE, SUIT_HEART);
const Card kTwoClub(CARD_VALUE_TWO, SUIT_CLUB);

GameModel CreateOldGameModel() {
  GameModel game_model;
  game_model.game_status.number_of_chairs = 6;
  return game_model;
}

}  // namespace

class SanityCheckTest : public testing::Test {
 public:
  SanityCheckTest() : kOldGameModel(CreateOldGameModel()) {
    // Change the counter threshold to fail instantly
    sanity_cheker_.counter_threshold_ = 0;
  }

 protected:
  const GameModel kOldGameModel;
  SanityCheck sanity_cheker_;
};
TEST_F(SanityCheckTest, ConstructDestruct) {
  EXPECT_EQ(sanity_cheker_.ErrorStr(), std::string());
}

TEST_F(SanityCheckTest, PassGameModel) {
  GameModel game_model;
  for (int i = DEALER_ONE; i < DEALER_MAX_SIZE; ++i) {
    EXPECT_EQ(game_model.dealer_cards[static_cast<DealerLocation>(i)],
              kUnknownCard);
  }

  // Expect true
  EXPECT_TRUE(sanity_cheker_.Check(kOldGameModel, &game_model));

  // Change the game_model and expect true
  game_model.player_hands[0].FirstCard() = kAceClub;
  game_model.player_hands[0].SecondCard() = kAceHeart;
  EXPECT_TRUE(sanity_cheker_.Check(kOldGameModel, &game_model));
}

TEST_F(SanityCheckTest, FailGameModel) {
  GameModel game_model;
  for (int i = DEALER_ONE; i < DEALER_MAX_SIZE; ++i) {
    EXPECT_EQ(game_model.dealer_cards[static_cast<DealerLocation>(i)],
              kUnknownCard);
  }

  game_model.dealer_cards[DEALER_ONE] = kTwoClub;
  // Expect TRUE because the new hand is the same as the old hand
  EXPECT_TRUE(sanity_cheker_.Check(kOldGameModel, &game_model));

  // Expect false because a new hand was dealt with a dealer card
  game_model.player_hands[0].FirstCard() = kAceClub;
  game_model.player_hands[0].SecondCard() = kAceHeart;
  EXPECT_FALSE(sanity_cheker_.Check(kOldGameModel, &game_model));
  std::cout << sanity_cheker_.ErrorStr();

  // Insert duplicates and expect false
  game_model.dealer_cards[DEALER_ONE] = kUnknownCard;
  game_model.player_hands[0].FirstCard() = kAceClub;
  game_model.player_hands[0].SecondCard() = kAceClub;
  EXPECT_FALSE(sanity_cheker_.Check(kOldGameModel, &game_model));
  std::cout << sanity_cheker_.ErrorStr();
}

}  // namespace poker
