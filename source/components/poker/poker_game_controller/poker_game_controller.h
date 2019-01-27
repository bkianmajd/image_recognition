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
#include <gtest/gtest_prod.h>

namespace poker {

// Converts images to decipher the workflow of a poker game
class PokerGameController : public PokerGameControllerInterface {
 public:
  PokerGameController(
      base::Callback<void(const PlayerHand&)> new_hand_callback,
      base::Callback<void(const GameModel&)> status_change_callback,
      base::Callback<void()> decision_callback,
      scoped_refptr<base::SingleThreadTaskRunner> callback_task_runner);

  ~PokerGameController() override = default;

  // Sets the data to process the image pipeline
  void UpdateBigImage(const std::vector<char>& big_image_raw_data) override;

  // Updates the model
  void UpdateModel();

 private:
  FRIEND_TEST(PokerGameControllerTest, NewHandTest);
  FRIEND_TEST(PokerGameControllerTest, GameModelTest);

  void CompareModelandNotify();
  bool CheckModelDifferent() const;
  bool CheckNewHand() const;

  GameModel last_game_model_;
  GameModel game_model_;

  LandmarkFinder landmark_finder_;

  const base::Callback<void(const PlayerHand&)> new_hand_callback_;
  const base::Callback<void(const GameModel&)> status_change_callback_;
  const base::Callback<void()> decision_callback_;
  scoped_refptr<base::SingleThreadTaskRunner> callback_task_runner_;
};

}  // namespace poker

#endif  // POKER_GAME_CONTROLLER_H_
