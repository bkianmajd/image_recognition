#ifndef POKER_WORKFLOW_H_
#define POKER_WORKFLOW_H_

#include <mutex>

#include "components/poker/entities/poker_workflow_callbacks.h"
#include "components/poker/poker_game_controller/poker_game_controller.h"

namespace poker {

class PokerWorkflow {
 public:
  PokerWorkflow();

  /// Consumes the image
  /// Comes from a different thread
  void ConsumeImage(std::vector<char>& big_image_raw_data);

  // Process the image
  void ProcessImage();

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

  std::mutex image_mutex_;
  std::vector<char> consumed_image_;
  int image_id_;
  int last_image_id_;

  PokerWorkflowCallbacks poker_workflow_callbacks_;
  std::unique_ptr<PokerGameController> poker_game_controller_;

  // TODO(): Change this to game state
  GameStatus game_status_;
};

}  // namespace poker

#endif  // POKER_WORKFLOW_H_
