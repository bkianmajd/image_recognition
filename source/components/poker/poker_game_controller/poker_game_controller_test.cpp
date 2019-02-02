#include "components/poker/poker_game_controller/poker_game_controller.h"

#include <iostream>

#include <base/bind.h>
#include <base/message_loop/message_loop.h>
#include <base/run_loop.h>

#include "gtest/gtest.h"

namespace poker {
namespace {

Card CreateTestCard() {
  Card card;
  card.value = CARD_VALUE_ACE;
  card.suit = SUIT_CLUB;
  return card;
}

void OnDecisionCallback() {}

void OnErrorCallback(const image::Image& image, const std::string& error_str) {
  (void)image;
  (void)error_str;
}

}  // namespace

class PokerGameControllerTest : public testing::Test {
 public:
  PokerGameControllerTest()
      : poker_game_controller_(
            base::Bind(&PokerGameControllerTest::OnNewHand,
                       base::Unretained(this)),
            base::Bind(&PokerGameControllerTest::OnStatusChange,
                       base::Unretained(this)),
            base::Bind(&OnDecisionCallback), base::Bind(&OnErrorCallback),
            message_loop_.task_runner()) {}

  void OnNewHand(const GameModel& game_model) {
    player_hand_ = game_model.player_hands[PLAYERLOC_PLAYER_ZERO];
  }

  void OnStatusChange(const GameModel& game_model) { game_model_ = game_model; }

 protected:
  PlayerHand player_hand_;
  GameModel game_model_;

  base::MessageLoop message_loop_;
  base::RunLoop run_loop_;
  PokerGameController poker_game_controller_;
};

TEST_F(PokerGameControllerTest, ConstructDestruct) {}

TEST_F(PokerGameControllerTest, NewHandTest) {
  PlayerHand player_hand;
  player_hand.first_card = CreateTestCard();
  player_hand.second_card = CreateTestCard();
  poker_game_controller_.game_model_.player_hands[PLAYERLOC_PLAYER_ZERO] =
      player_hand;
  poker_game_controller_.CompareModelandNotify();

  run_loop_.RunUntilIdle();

  EXPECT_EQ(player_hand_.first_card, player_hand.first_card);
  EXPECT_EQ(player_hand_.second_card, player_hand.second_card);
}

TEST_F(PokerGameControllerTest, GameModelTest) {
  GameModel game_model;
  game_model.game_status.number_of_chairs = 2;
  game_model.dealer_cards[DEALER_ONE] = CreateTestCard();
  // Set the game model
  poker_game_controller_.game_model_ = game_model;

  // The game model should be different from the |last_game_model_)
  EXPECT_TRUE(poker_game_controller_.CheckModelDifferent());

  // The game controller should post a task to the callback
  poker_game_controller_.CompareModelandNotify();
  run_loop_.RunUntilIdle();

  // The test |game_model_| should be updated
  EXPECT_EQ(game_model_.game_status.number_of_chairs,
            game_model.game_status.number_of_chairs);
  EXPECT_EQ(game_model_.dealer_cards, game_model.dealer_cards);
}

}  // namespace poker
