#ifndef POKER_GAME_CONTROLLER_H_
#define POKER_GAME_CONTROLLER_H_

#include "components/poker/entities/poker_workflow_callbacks.h"

namespace poker {

class PokerGameController {
 public:
  PokerGameController(const PokerWorkflowCallbacks& poker_workflow_callbacks, bool unit_testing);

  void ProcessBigImage(const std::vector<char>& big_image_raw_data );

 private:
  PokerWorkflowCallbacks poker_workflow_callbacks_;
};

}  // namespace poker

#endif  // POKER_GAME_CONTROLLER_H_
