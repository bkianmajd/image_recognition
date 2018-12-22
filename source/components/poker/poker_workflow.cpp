#include "components/poker/poker_workflow.h"

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

PokerWorkflow::PokerWorkflow() : image_id_(0), last_image_id_(0) {
  consumed_image_.clear();
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
}

void PokerWorkflow::ProcessImage() {
  {
    std::lock_guard<std::mutex> lock(image_mutex_);
    if (image_id_ == last_image_id_) {
      return;
    }
    image_id_ = last_image_id_;
    poker_game_controller_->UpdateBigImage(consumed_image_);
    // No longer need the image data
    consumed_image_.clear();
  }

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

void PokerWorkflow::ConsumeImage(std::vector<char>& big_image_raw_data) {
  std::lock_guard<std::mutex> lock(image_mutex_);
  std::cout << "Consuming image " << big_image_raw_data.size() << std::endl;
  std::swap(consumed_image_, big_image_raw_data);
  image_id_++;
}

void PokerWorkflow::OnFlop(Card first_card, Card second_card, Card third_card) {
  std::cout << "Flop detected " << first_card << " " << second_card << " "
            << third_card << std::endl;
}

void PokerWorkflow::OnTurn(Card fourth_card) {
  std::cout << "fourth card detected " << fourth_card << std::endl;
}
void PokerWorkflow::OnRiver(Card fifth_card) {
  std::cout << "fifth card detected " << fifth_card << std::endl;
}

void PokerWorkflow::OnPlayerDeal(Card left_card, Card right_card) {
  std::cout << "player deal" << left_card << " " << right_card << std::endl;
}

void PokerWorkflow::OnReset() { std::cout << "reset called" << std::endl; }

}  // namespace poker
