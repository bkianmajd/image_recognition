#include "components/poker/poker_workflow.h"

#include <functional>

namespace poker {

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

  // Player actions
  poker_workflow_callbacks_.OnPlayerFold =
      std::bind(&PokerWorkflow::OnPlayerFold, this);
}

void PokerWorkflow::OnFlop(Card first_card, Card second_card, Card third_card) {

}

void PokerWorkflow::OnTurn(Card fourth_card) {}
void PokerWorkflow::OnRiver(Card fifth_card) {}

void PokerWorkflow::OnPlayerDeal(Card left_card, Card right_card) {}

void PokerWorkflow::OnReset() {}

void PokerWorkflow::OnPlayerFold() {}

}  // namespace poker
