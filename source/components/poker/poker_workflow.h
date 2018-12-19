#ifndef POKER_WORKFLOW_H_
#define POKER_WORKFLOW_H_

#include "components/poker/entities/poker_workflow_callbacks.h"

namespace poker {

class PokerWorkflow {
 public:
  PokerWorkflow();

 private:
  // Dealer actions
  void OnFlop(Card first_card, Card second_card, Card third_card);
  void OnTurn(Card fourth_card);
  void OnRiver(Card fifth_card);

  // Game actions
  void OnPlayerDeal(Card left_card, Card right_card);
  // Resets mean the game hand has ended
  void OnReset();

  // Player actions
  void OnPlayerFold();

  PokerWorkflowCallbacks poker_workflow_callbacks_;
};

}  // namespace poker

#endif  // POKER_WORKFLOW_H_
