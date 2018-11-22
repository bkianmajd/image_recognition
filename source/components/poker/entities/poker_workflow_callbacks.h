#ifndef POKER_WORKFLOW_CALLBACKS_H_
#define POKER_WORKFLOW_CALLBACKS_H_

#include <functional>
#include <string>
#include <vector>

#include "components/poker/entities/card_def.h"

/// Sums up the events of a poker game
namespace poker {

struct PokerWorkflowCallbacks {
  std::function<void(const std::string& player)> OnPlayerEntering;

  std::function<void(const std::string& player)> OnPlayerExiting;

  std::function<void(const std::string& player, float call_amount)>
      OnPlayerCall;

  std::function<void(const std::string& player)> OnPlayerFold;
};

}  // poker

#endif  // POKER_WORKFLOW_CALLBACKS_H_
