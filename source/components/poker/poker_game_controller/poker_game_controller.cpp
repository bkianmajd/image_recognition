#include "components/poker/poker_game_controller/poker_game_controller.h"

#include <algorithm>

namespace poker {
namespace {

// TODO(): Generate mocks here through a factory
constexpr int kDefualtChairs = 6;

}  // namespace

PokerGameController::PokerGameController(
    PokerWorkflowCallbacks* poker_workflow_callbacks)
    : poker_workflow_callbacks_(poker_workflow_callbacks),
      landmark_finder_(kDefualtChairs) {}

void PokerGameController::UpdateBigImage(
    const std::vector<char>& big_image_raw_data) {
  // Updates the landmark_finder with the new screenshot
  landmark_finder_.UpdateBigImage(big_image_raw_data);
}

bool PokerGameController::ProcessNextWorkflow(const GameStatus& game_status) {
  std::swap(last_game_status_, current_game_status_);
  current_game_status_ = game_status;

  // TODO() : Consider doing game states here, i.e. player_waiting_preflop,
  // player_waiting_flop, or player_betting_preflop...etc,

  // Checks to see if the dealer dealt a new card on the table
  if (CheckTableStatus()) {
    return true;
  }

  // Checks to see if the player status has changed
  return CheckPlayerStatus();
}

bool PokerGameController::CheckPlayerStatus() {
  bool event_triggered = false;

  switch (current_game_status_.player_status[0]) {
    case PlayerStatus::PLAYER_STATUS_FOLDED:
      event_triggered = CheckForNewHandEvent();
      break;
    case PlayerStatus::PLAYER_STATUS_IN_HAND:
      event_triggered = CheckForDecisionEvent();
      break;
    case PlayerStatus::PLAYER_STATUS_OUTSIDE:
      break;
    default:
      break;
  }

  return event_triggered;
}

bool PokerGameController::CheckForDecisionEvent() {
  // TODO(): Checks to see if the player needs to check, fold, raise, or bet
  return false;
}

bool PokerGameController::CheckForNewHandEvent() {
  Card left_card = landmark_finder_.FindLeftCard(PLAYERLOC_PLAYER_ZERO);
  if (left_card.card_value == CARD_VALUE_UNKNOWN) {
    return false;
  }

  Card right_card = landmark_finder_.FindLeftCard(PLAYERLOC_PLAYER_ZERO);
  if (right_card.card_value == CARD_VALUE_UNKNOWN) {
    return false;
  }

  poker_workflow_callbacks_->OnPlayerDeal(left_card, right_card);
  return true;
}

bool PokerGameController::CheckTableStatus() {
  bool event_triggered = false;

  // Check the game_model for the next steps
  switch (current_game_status_.table_status) {
    case TABLE_STATUS_UNKNOWN:
    case TABLE_STATUS_PREFLOP:
      event_triggered = CheckForFlopEvent();
    break;
    case TABLE_STATUS_FLOP:
      event_triggered = CheckForTurnEvent();
      break;
    case TABLE_STATUS_TURN:
      event_triggered = CheckForRiverEvent();
      break;
    case TABLE_STATUS_RIVER:
      event_triggered = CheckForRoundEndEvent();
      break;
    default:
      std::cerr << "Switch statement not handled!" << std::endl;
  }

  return event_triggered;
}

bool PokerGameController::CheckForRoundEndEvent() {
  Card card_one = landmark_finder_.FindDealerCard(DealerLocation::DEALER_ONE);
  if (card_one.card_value != CARD_VALUE_UNKNOWN) {
    return false;
  }

  poker_workflow_callbacks_->OnReset();
  return true;
}

bool PokerGameController::CheckForFlopEvent() {
  Card card_one = landmark_finder_.FindDealerCard(DealerLocation::DEALER_ONE);
  if (card_one.card_value == CARD_VALUE_UNKNOWN) {
    return false;
  }

  Card card_two = landmark_finder_.FindDealerCard(DealerLocation::DEALER_TWO);
  if (card_two.card_value == CARD_VALUE_UNKNOWN) {
    return false;
  }

  Card card_three =
      landmark_finder_.FindDealerCard(DealerLocation::DEALER_THREE);
  if (card_three.card_value == CARD_VALUE_UNKNOWN) {
    return false;
  }

  poker_workflow_callbacks_->OnFlop(card_one, card_two, card_three);
  return true;
}

bool PokerGameController::CheckForTurnEvent() {
  Card card = landmark_finder_.FindDealerCard(DealerLocation::DEALER_FOUR);
  if (card.card_value == CARD_VALUE_UNKNOWN) {
    return false;
  }

  poker_workflow_callbacks_->OnTurn(card);
  return true;
}

bool PokerGameController::CheckForRiverEvent() {
  Card card = landmark_finder_.FindDealerCard(DealerLocation::DEALER_FIVE);
  if (card.card_value == CARD_VALUE_UNKNOWN) {
    return false;
  }

  poker_workflow_callbacks_->OnRiver(card);
  return true;
}

}  // namespace poker
