#include "components/poker/poker_game_controller/poker_game_controller.h"

#include "components/poker/entities/comparator/comparator.h"

#include <algorithm>

#include <base/bind.h>

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
    base::Callback<void(const GameModel&)> new_hand_callback,
    base::Callback<void(const GameModel&)> status_change_callback,
    base::Callback<void()> decision_callback,
    base::Callback<void(const image::Image&, const std::string& error_str)>
        error_callback,
    scoped_refptr<base::SingleThreadTaskRunner> callback_task_runner)
    : last_game_model_(InitialGameModel()),
      game_model_(InitialGameModel()),
      landmark_finder_(kDefualtChairs),
      new_hand_callback_(new_hand_callback),
      status_change_callback_(status_change_callback),
      decision_callback_(decision_callback),
      error_callback_(error_callback),
      callback_task_runner_(callback_task_runner) {
  assert(callback_task_runner != nullptr);
}

void PokerGameController::UpdateBigImage(
    const std::vector<char>& big_image_raw_data) {
  // Updates the landmark_finder with the new screenshot
  landmark_finder_.UpdateBigImage(big_image_raw_data);
  UpdateModel();

  if (!sanity_check_.Check(last_game_model_, &game_model_)) {
    callback_task_runner_->PostTask(
        FROM_HERE, base::Bind(error_callback_, big_image_raw_data,
                              sanity_check_.ErrorStr()));
  }

  // Post tasks based on inferring from the game model
  CompareModelandNotify();

  // Swap the |last_game_model_| becasue the next update is going to change the
  // current game model anyways.
  std::swap(last_game_model_, game_model_);
}

void PokerGameController::UpdateModel() {
  for (int i = 0; i < kDefualtChairs; ++i) {
    PlayerHand& player_hand = game_model_.player_hands[static_cast<size_t>(i)];
    player_hand.FirstCard() =
        landmark_finder_.FindLeftCard(static_cast<PlayerLocation>(i));
    player_hand.SecondCard() =
        landmark_finder_.FindRightCard(static_cast<PlayerLocation>(i));
  }

  for (int i = DEALER_ONE; i < DEALER_MAX_SIZE; ++i) {
    Card& dealer_card = game_model_.dealer_cards[static_cast<size_t>(i)];
    dealer_card =
        landmark_finder_.FindDealerCard(static_cast<DealerLocation>(i));
  }
}

void PokerGameController::CompareModelandNotify() {
  if (CheckForNewHand(last_game_model_, game_model_)) {
    callback_task_runner_->PostTask(
        FROM_HERE, base::Bind(new_hand_callback_, game_model_));
    return;
  }

  if (CheckModelDifferent()) {
    callback_task_runner_->PostTask(
        FROM_HERE, base::Bind(status_change_callback_, game_model_));

    return;
  }

  if (landmark_finder_.FindDecisionEvent()) {
    callback_task_runner_->PostTask(FROM_HERE, decision_callback_);
    return;
  }
}

bool PokerGameController::CheckModelDifferent() const {
  for (int i = 0; i < kDefualtChairs; ++i) {
    const PlayerHand& player_hand =
        game_model_.player_hands[static_cast<size_t>(i)];
    const PlayerHand& old_player_hand =
        last_game_model_.player_hands[static_cast<size_t>(i)];
    if (player_hand.FirstCard() != old_player_hand.FirstCard()) {
      return true;
    }
    if (player_hand.SecondCard() != old_player_hand.SecondCard()) {
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
  return false;
}

}  // namespace poker
