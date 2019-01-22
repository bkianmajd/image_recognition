#ifndef POKER_GAME_CONTROLLER_H_
#define POKER_GAME_CONTROLLER_H_

#include "components/poker/poker_game_controller/poker_game_controller_interface.h"

#include <vector>

#include "components/poker/entities/game_model_def.h"
#include "components/poker/entities/poker_workflow_callbacks.h"
#include "components/poker/poker_game_controller/landmark_finder/landmark_finder.h"

#include <base/callback.h>
#include <base/single_thread_task_runner.h>
#include <base/task_runner.h>

namespace poker {

// Converts images to decipher the workflow of a poker game
class PokerGameController : public PokerGameControllerInterface {
 public:
  PokerGameController(
      base::Callback<void(const Card&)> new_hand_callback,
      base::Callback<void(const GameModel&)> status_change_callback,
      scoped_refptr<base::SingleThreadTaskRunner> task_runner);

  ~PokerGameController() override = default;

  // Sets the data to process the image pipeline
  void UpdateBigImage(const std::vector<char>& big_image_raw_data) override;

  // Updates the model
  void UpdateModel();

 private:
  void CompareModelandNotify();
  bool CheckModelDifferent() const;
  bool CheckNewHand() const;

  PokerWorkflowCallbacks* poker_workflow_callbacks_;
  LandmarkFinder landmark_finder_;

  GameModel last_game_model_;
  GameModel game_model_;

  base::Callback<void(const Card&)> new_hand_callback_;
  base::Callback<void(const GameModel&)> status_change_callback_;
  base::Callback<void()> error_callback_;
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
};

}  // namespace poker

#endif  // POKER_GAME_CONTROLLER_H_
