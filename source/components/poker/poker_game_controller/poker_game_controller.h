#ifndef POKER_GAME_CONTROLLER_H_
#define POKER_GAME_CONTROLLER_H_

#include "components/poker/entities/poker_workflow_callbacks.h"

#include "components/poker/entities/game_model_def.h"
#include "components/poker/poker_game_controller/landmark_finder/landmark_finder.h"

namespace poker {

// Converts images to decipher the workflow of a poker game
class PokerGameController {
 public:
  explicit PokerGameController(
      PokerWorkflowCallbacks* poker_workflow_callbacks);

  // Sets the data to process the image pipeline
  void UpdateBigImage(const std::vector<char>& big_image_raw_data);

  // Returns true if there is still more to progress through the workflow
  bool ProcessNextWorkflow(const GameStatus& game_status);

 private:
  bool CheckPlayerStatus();
  bool CheckForNewHandEvent();
  bool CheckForDecisionEvent();

  bool CheckTableStatus();
  bool CheckForFlopEvent();
  bool CheckForTurnEvent();
  bool CheckForRiverEvent();
  bool CheckForRoundEndEvent();

  PokerWorkflowCallbacks* poker_workflow_callbacks_;
  LandmarkFinder landmark_finder_;

  GameStatus current_game_status_;
  GameStatus last_game_status_;
};

}  // namespace poker

#endif  // POKER_GAME_CONTROLLER_H_
