#include "components/poker/poker_game_controller/poker_game_controller.h"

#include <algorithm>

namespace poker {
namespace {

// TODO(): Generate mocks here through a factory
constexpr int kDefualtChairs = 6;

GameModel InitialGameModel() {
  GameModel game_model;
  game_model.game_status.number_of_chairs = kDefualtChairs;
  return game_model;
}

}  // namespace

PokerGameController::PokerGameController(
    base::Callback<void(const Card&)> new_hand_callback,
    base::Callback<void(const GameModel&)> status_change_callback,
    scoped_refptr<base::SingleThreadTaskRunner> task_runner)
    : landmark_finder_(kDefualtChairs),
      last_game_model_(InitialGameModel()),
      game_model_(InitialGameModel()),
      new_hand_callback_(new_hand_callback),
      status_change_callback_(status_change_callback),
      task_runner_(task_runner) {}

void PokerGameController::UpdateBigImage(
    const std::vector<char>& big_image_raw_data) {
  // Updates the landmark_finder with the new screenshot
  landmark_finder_.UpdateBigImage(big_image_raw_data);
  UpdateModel();

  // Sanity check Model
  // if(!sanity_check_.Check(last_game_model_, &game_model_)) {
  // Post error
  // return;
  //}

  CompareModelandNotify();

  // Swap the |last_game_model_| becasue the next update is going to change the
  // current game model anyways.
  std::swap(last_game_model_, game_model_);
}

void PokerGameController::UpdateModel() {
  for (int i = 0; i < kDefualtChairs; ++i) {
    PlayerHand& player_hand = game_model_.player_hands[static_cast<size_t>(i)];
    player_hand.first_card =
        landmark_finder_.FindLeftCard(static_cast<PlayerLocation>(i));
    player_hand.second_card =
        landmark_finder_.FindRightCard(static_cast<PlayerLocation>(i));
  }

  for (int i = 0; i <= DEALER_FIVE; ++i) {
    Card& dealer_card = game_model_.dealer_cards[static_cast<size_t>(i)];
    dealer_card =
        landmark_finder_.FindDealerCard(static_cast<DealerLocation>(i));
  }
}

void PokerGameController::CompareModelandNotify() {
  if (CheckNewHand()) {
    // post task
    return;
  }

  if (CheckModelDifferent()) {
    // post task
    return;
  }

  if (landmark_finder_.FindDecisionEvent()) {
    // post task
    return;
  }
}

bool PokerGameController::CheckModelDifferent() const {
  for (int i = 0; i < kDefualtChairs; ++i) {
    const PlayerHand& player_hand =
        game_model_.player_hands[static_cast<size_t>(i)];
    const PlayerHand& old_player_hand =
        last_game_model_.player_hands[static_cast<size_t>(i)];
    if (player_hand.first_card != old_player_hand.first_card) {
      return true;
    }
    if (player_hand.second_card != old_player_hand.second_card) {
      return true;
    }
  }

  for (int i = DEALER_ONE; i < DEALER_MAX_SIZE; ++i) {
    const Card& dealer_card = game_model_.dealer_cards[static_cast<size_t>(i)];
    const Card& old_dealer_card =
        last_game_model_.dealer_cards[static_cast<size_t>(i)];

    if (dealer_card != old_dealer_card) {
      return true;
    }
  }

  // Model is the same
  return true;
}

bool PokerGameController::CheckNewHand() const {
  // if this is unknown, the right card and suit should be unknown as well
  if (game_model_.player_hands[PLAYERLOC_PLAYER_ZERO].first_card.value ==
      CARD_VALUE_UNKNOWN) {
    return false;
  }

  if (game_model_.player_hands[PLAYERLOC_PLAYER_ZERO].first_card ==
      last_game_model_.player_hands[PLAYERLOC_PLAYER_ZERO].first_card) {
    return false;
  }

  return true;
}

}  // namespace poker
