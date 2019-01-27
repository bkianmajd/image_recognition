#include "components/poker/workflow_session.h"

#include <functional>

#include "components/poker/poker_game_controller/poker_game_controller.h"
#include "components/poker/poker_game_controller/training/training_game_controller.h"
#include "helpers/memory_helper.hpp"

namespace poker {
namespace {
constexpr bool training = false;

}  // namespace

WorkflowSession::WorkflowSession(
    scoped_refptr<base::SingleThreadTaskRunner> workflow_task_runner)
    : workflow_task_runner_(workflow_task_runner) {
  // Starting threads
  if (training) {
    game_controller_session_.StartSession<TrainingGameController>();
    return;
  }

  // Constructing PokerGameController
  game_controller_session_.StartSession<PokerGameController>(
      base::Bind(&WorkflowSession::OnNewHand, base::Unretained(this)),
      base::Bind(&WorkflowSession::OnGameModelUpdate, base::Unretained(this)),
      base::Bind(&WorkflowSession::OnPokerDecision, base::Unretained(this)),
      workflow_task_runner_);
}

void WorkflowSession::ProcessImage(const image::Image& image) {
  // This should invoke some callbacks back to this thread
  game_controller_session_.task_runner()->PostTask(
      FROM_HERE,
      base::Bind(&PokerGameControllerInterface::UpdateBigImage,
                 base::Unretained(game_controller_session_.get()), image));
}

void WorkflowSession::OnNewHand(const PlayerHand& player_hand) {
  std::cout << "Player deal " << player_hand.first_card << " "
            << player_hand.second_card << std::endl << std::endl;
}

void WorkflowSession::OnGameModelUpdate(const GameModel& game_model) {
  game_model_.game_status = game_model.game_status;
  game_model_.dealer_cards = game_model.dealer_cards;
  game_model_.player_hands = game_model.player_hands;

  ////---debug-----///
  static int counter = 0;
  std::cout << "Game model update " << counter++ << std::endl;

  // Print out the dealer cards
  std::cout << "D: ";
  for (size_t i = DEALER_ONE; i < DEALER_MAX_SIZE; ++i) {
    std::cout << game_model_.dealer_cards.at(i);
    std::cout << " ";
  }
  std::cout << std::endl << std::endl;

  // Print out player cards
  for (size_t i = PLAYERLOC_PLAYER_ZERO; i < PLAYERLOC_PLAYER_SIX; ++i) {
    std::cout << "P[" << i << "] " << game_model_.player_hands[i];
  }
  std::cout << std::endl;
}

void WorkflowSession::OnPokerDecision() {
  std::cout << "poker decision needs to be made" << std::endl;
}

}  // namespace poker
