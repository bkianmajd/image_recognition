#include "components/poker/poker_workflow.h"

#include <functional>

namespace poker {
namespace {
constexpr int kTimeout = 100;
}  // namespace

PokerWorkflow::PokerWorkflow() {
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
}

void PokerWorkflow::ProcessImage() {
  {
    std::lock_guard<std::mutex> lock(image_mutex_);
    if (image_id_ == last_image_id_) {
      return;
    }
    image_id_ = last_image_id_;
    poker_game_controller_->UpdateBigImage(active_image_);
  }

  // Work on the active_image
  int running_counter = 0;
  while (running_counter++ < kTimeout) {
    // This should invoke some callbacks on this thread
    if (!poker_game_controller_->ProcessNextWorkflow()) {
      return;
    }
  }

  std::cerr << "Timeout occured, workflow stuck" << std::endl;
}

void PokerWorkflow::ConsumeImage(std::vector<char>& big_image_raw_data) {
  std::lock_guard<std::mutex> lock(image_mutex_);
  std::swap(active_image_, big_image);
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
