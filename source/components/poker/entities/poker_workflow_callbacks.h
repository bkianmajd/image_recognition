#ifndef POKER_WORKFLOW_CALLBACKS_H_
#define POKER_WORKFLOW_CALLBACKS_H_

#include <functional>
#include <string>
#include <vector>

#include "components/poker/entities/card_def.h"

/// Sums up the events of a poker game
namespace poker {

struct PokerWorkflowCallbacks {
  // Table status
  std::function<void(const std::string& player)> OnPlayerEntering;

  std::function<void(const std::string& player)> OnPlayerExiting;

  // Card bets
  std::function<void(Card first_card, Card second_card, Card third_card)>
      OnFlop;

  std::function<void(Card fourth_card)> OnTurn;

  std::function<void(Card fifth_card)> OnRiver;

  std::function<void()> OnReset;

  // Player actions
  std::function<void(Card left_card, Card right_card)> OnPlayerDeal;
};

}  // poker

#endif  // POKER_WORKFLOW_CALLBACKS_H_
