#include "components/poker/workflow_session.h"

#include <functional>

#include "components/poker/poker_decider/simple_decider/simple_decider.h"
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
    return std::make_unique<WorkflowDebugger>(DebugType::PRINT_WORKFLOW_MODEL);
  }
  return std::make_unique<WorkflowDebuggerMock>();
}

}  // namespace

WorkflowSession::WorkflowSession()
    : poker_decider_interface_(std::make_unique<SimpleDecider>()),
      workflow_debugger_(CreateWorkflowDebugger()) {
  // Starting threads
  if (training) {
    game_controller_.reset(new TrainingGameController());
    return;
  }

  // Constructing PokerGameController
  game_controller_.reset(new PokerGameController(
      base::Bind(&WorkflowSession::OnNewHand, base::Unretained(this)),
      base::Bind(&WorkflowSession::OnGameModelUpdate, base::Unretained(this)),
      base::Bind(&WorkflowSession::OnPokerDecision, base::Unretained(this)),
      base::Bind(&WorkflowSession::OnError, base::Unretained(this))));
}

void WorkflowSession::ProcessImage(const image::Image& narrowed_image) {
  recorded_ = false;
  last_image_ = narrowed_image;
  // This should invoke some callbacks back to this thread
  game_controller_->UpdateBigImage(last_image_);
}

void WorkflowSession::InjectNewHand(const PlayerHand& player_hand) {
  // Need to figure out a way to reset this
  injected_hand_ = player_hand;
  std::cout << "hand is injected" << std::endl;
}

void WorkflowSession::ClearInjection() { injected_hand_ = base::nullopt; }

void WorkflowSession::OnNewHand(const GameModel& game_model) {
  if (injected_hand_.has_value()) {
    GameModel mock_model = game_model;
    mock_model.player_hands[0] = injected_hand_.value();
    workflow_model_builder_.reset(new WorkflowModelBuilder(mock_model));
    workflow_debugger_->PrintNewHand(mock_model);
    return;
  }

  workflow_debugger_->PrintNewHand(game_model);
  if (game_model.player_hands[0].FirstCard().suit == SUIT_UNKNOWN) {
    return;
  }
  workflow_model_builder_.reset(new WorkflowModelBuilder(game_model));
}

void WorkflowSession::OnGameModelUpdate(const GameModel& game_model) {
  if (!workflow_model_builder_) {
    return;
  }

  workflow_debugger_->PrintStatusChange(game_model);
  workflow_model_builder_->HandleGameModelChange(game_model);
  workflow_debugger_->PrintStatusChange(workflow_model_builder_->GetModel());
}

void WorkflowSession::ForceDecision() { OnPokerDecision(); }

void WorkflowSession::OnPokerDecision() {
  if (!workflow_model_builder_) {
    // Should fold if this ever happens
    std::cerr << "model build is nullptr" << std::endl;
    return;
  }
  // Poker decision needs to be made
  Decision decision =
      poker_decider_interface_->Deicide(workflow_model_builder_->GetModel());

  std::cout << "Decision is to: " << decision.decisionType << std::endl;
}

void WorkflowSession::OnError(const image::Image& error_image,
                              const std::string& error_str) {
  // If an image fails the sanity check, store the image to loop back for
  // training offline
  workflow_debugger_->StoreError(error_image, error_str);
}

void WorkflowSession::SaveImageToDebug(const std::string& file_abs_path) {
  if(recorded_) {
    return;
  }
  recorded_ = true;
  helpers::FileManager::StoreFile(last_image_.data(), last_image_.size(),
                                  file_abs_path);
}

}  // namespace poker
