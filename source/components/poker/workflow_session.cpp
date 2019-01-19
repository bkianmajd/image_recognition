#include "components/poker/workflow_session.h"

#include <functional>

#include "components/poker/poker_game_controller/poker_game_controller.h"
#include "components/poker/poker_game_controller/training/training_game_controller.h"
#include "helpers/memory_helper.hpp"

namespace poker {
namespace {
constexpr int kTimeout = 100;
constexpr bool training = true;

std::unique_ptr<PokerGameControllerInterface> GameControllerFactory(
    PokerWorkflowCallbacks* workflow_callbacks) {
  if (training) {
    return std::make_unique<TrainingGameController>();
  }

  return std::make_unique<PokerGameController>(workflow_callbacks);
}

}  // namespace

WorkflowSession::WorkflowSession() : image_id_(0), last_image_id_(0) {
  consumed_image_.clear();

  // TODO(): Use callbacks
  // base::Callback<void()> test = base::Bind([](){});
  // task_runner_->PostTask(FROM_HERE, test);

  /*
  // Dealer actions
  poker_workflow_callbacks_.OnFlop =
      std::bind(&PokerWorkflow::OnFlop, this, std::placeholders::_1,
                std::placeholders::_2, std::placeholders::_3);
  poker_workflow_callbacks_.OnTurn =
      std::bind(&PokerWorkflow::OnTurn, this, std::placeholders::_1);
  poker_workflow_callbacks_.OnRiver =
      std::bind(&PokerWorkflow::OnRiver, this, std::placeholders::_1);

  // Game actions
  poker_workflow_callbacks_.OnPlayerDeal =
      std::bind(&PokerWorkflow::OnPlayerDeal, this, std::placeholders::_1,
                std::placeholders::_2);
  poker_workflow_callbacks_.OnReset = std::bind(&PokerWorkflow::OnReset, this);

  // Instantiate the game controller
  poker_game_controller_ = GameControllerFactory(&poker_workflow_callbacks_);
  */
}

void WorkflowSession::ProcessImage(const image::Image& image) {
  poker_game_controller_->UpdateBigImage(consumed_image_);


  // Work on image inside the game controller
  int running_counter = 0;
  while (running_counter++ < kTimeout) {
    // This should invoke some callbacks on this thread
    if (!poker_game_controller_->ProcessNextWorkflow(game_status_)) {
      return;
    }
  }

  std::cerr << "Timeout occured, workflow stuck" << std::endl;
}


void WorkflowSession::OnFlop(Card first_card, Card second_card,
                             Card third_card) {
  std::cout << "Flop detected " << first_card << " " << second_card << " "
            << third_card << std::endl;
}

void WorkflowSession::OnTurn(Card fourth_card) {
  std::cout << "fourth card detected " << fourth_card << std::endl;
}
void WorkflowSession::OnRiver(Card fifth_card) {
  std::cout << "fifth card detected " << fifth_card << std::endl;
}

void WorkflowSession::OnPlayerDeal(Card left_card, Card right_card) {
  std::cout << "player deal" << left_card << " " << right_card << std::endl;
}

void WorkflowSession::OnReset() { std::cout << "reset called" << std::endl; }

}  // namespace poker
