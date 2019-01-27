#include "components/poker/workflow_session.h"

#include <functional>

#include "components/poker/poker_game_controller/poker_game_controller.h"
#include "components/poker/poker_game_controller/training/training_game_controller.h"
#include "components/poker/workflow_debugger/workflow_debugger.h"
#include "components/poker/workflow_debugger/workflow_debugger_mock.h"
#include "helpers/memory_helper.hpp"

namespace poker {
namespace {
constexpr bool training = false;
constexpr bool debugging = true;

std::unique_ptr<WorkflowDebuggerInterface> CreateWorkflowDebugger() {
  if (debugging) {
    return std::make_unique<WorkflowDebugger>();
  }
  return std::make_unique<WorkflowDebuggerMock>();
}

}  // namespace

WorkflowSession::WorkflowSession(
    scoped_refptr<base::SingleThreadTaskRunner> workflow_task_runner)
    : workflow_task_runner_(workflow_task_runner),
      workflow_debugger_(CreateWorkflowDebugger()) {
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
      base::Bind(&WorkflowSession::OnError, base::Unretained(this)),
      workflow_task_runner_);
}

void WorkflowSession::ProcessImage(const image::Image& image) {
  // This should invoke some callbacks back to this thread
  game_controller_session_.task_runner()->PostTask(
      FROM_HERE,
      base::Bind(&PokerGameControllerInterface::UpdateBigImage,
                 base::Unretained(game_controller_session_.get()), image));
}

void WorkflowSession::OnNewHand(const GameModel& game_model) {
  workflow_debugger_->PrintNewHand(game_model);
}

void WorkflowSession::OnGameModelUpdate(const GameModel& game_model) {
  game_model_.game_status = game_model.game_status;
  game_model_.dealer_cards = game_model.dealer_cards;
  game_model_.player_hands = game_model.player_hands;

  workflow_debugger_->PrintStatusChange(game_model);
}

void WorkflowSession::OnPokerDecision() {
  std::cout << "poker decision needs to be made" << std::endl;
}

void WorkflowSession::OnError(const image::Image& error_image,
                              const std::string& error_str) {
  // If an image fails the sanity check, store the image to loop back for
  // training offline
  workflow_debugger_->StoreError(error_image, error_str);
}

}  // namespace poker
