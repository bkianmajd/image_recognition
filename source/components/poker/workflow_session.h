#ifndef WORKFLOW_SESSION_H_
#define WORKFLOW_SESSION_H_

#include <memory>
#include <mutex>

#include "components/poker/entities/poker_workflow_callbacks.h"
#include "components/poker/poker_game_controller/poker_game_controller_interface.h"
#include "libraries/image_def/image_def.h"
#include "libraries/session_thread/session_thread.h"

namespace poker {

class WorkflowSession {
 public:
  explicit WorkflowSession(scoped_refptr<base::SingleThreadTaskRunner> task_runner);

  /// Process the image
  void ProcessImage(const image::Image& big_image_raw_data);

 private:
  void OnNewHand(const Card& card);
  void OnGameModelUpdate(const GameModel& game_model);
  void OnError();

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

  GameStatus game_status_;

  // The workflow's thread corresponding taskrunner
  scoped_refptr<base::SingleThreadTaskRunner> workflow_task_runner_;

  // Interactors
  SessionThread<PokerGameControllerInterface> game_controller_session_;
};

}  // namespace poker

#endif  // WORKFLOW_SESSION_H_
