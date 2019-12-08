#include "components/poker/workflow_model_builder.h"

namespace poker {

WorkflowModelBuilder::WorkflowModelBuilder(const GameModel& game_model) {
  workflow_model_.number_of_original_opponents =
      FindActiveOpponents(game_model);
  workflow_model_.player_hand = game_model.player_hands[0];
}

void WorkflowModelBuilder::HandleGameModelChange(const GameModel& game_model) {
  workflow_model_.dealer_cards = game_model.dealer_cards;
  workflow_model_.workflow_state = FindCurrentState(game_model);
  workflow_model_.number_of_active_opponents = FindActiveOpponents(game_model);
  // TODO(BK): Build built in self test here
}

WorkflowModel WorkflowModelBuilder::GetModel() const { return workflow_model_; }

WorkflowState WorkflowModelBuilder::FindCurrentState(
    const GameModel& game_model) const {
  if (game_model.dealer_cards[0].suit == SUIT_UNKNOWN ||
      game_model.dealer_cards[0].suit == SUIT_HIDDEN) {
    return WorkflowState::PREFLOP;
  }
  if (game_model.dealer_cards[3].suit == SUIT_UNKNOWN ||
      game_model.dealer_cards[3].suit == SUIT_HIDDEN) {
    return WorkflowState::FLOP;
  }
  if (game_model.dealer_cards[4].suit == SUIT_UNKNOWN ||
      game_model.dealer_cards[4].suit == SUIT_HIDDEN) {
    return WorkflowState::TURN;
  }
  return WorkflowState::RIVER;
}

int WorkflowModelBuilder::FindActiveOpponents(
    const GameModel& game_model) const {
  int number_of_active_opponents = 0;
  for (size_t i = 0; i < game_model.player_hands.size(); ++i) {
    if (i == 0) {
      continue;
    }
    if (game_model.player_hands[i].FirstCard().suit != SUIT_HIDDEN ||
        game_model.player_hands[i].SecondCard().suit != SUIT_HIDDEN) {
      continue;
    }

    number_of_active_opponents++;
  }
  return number_of_active_opponents;
}

}  // namespace poker
