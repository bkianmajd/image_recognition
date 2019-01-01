#ifndef TRAINING_GAME_CONTROLLER_H_
#define TRAINING_GAME_CONTROLLER_H_

#include <chrono>

#include "components/poker/poker_game_controller/poker_game_controller_interface.h"
#include "components/poker/poker_game_controller/landmark_finder/landmark_finder.h"
#include "helpers/directory_finder.h"

namespace poker {

// Converts images to decipher the workflow of a poker game
class TrainingGameController : public PokerGameControllerInterface {
 public:
  TrainingGameController();

  // Sets the data to process the image pipeline
  void UpdateBigImage(const std::vector<char>& big_image_raw_data) override;

  // Returns true if there is still more to progress through the workflow
  bool ProcessNextWorkflow(const GameStatus& game_status) override;

 private:
  void TakeScreenshots(const std::vector<char>& big_image_raw_data);
  void ReadCards(const std::vector<char>& big_image_raw_data);


  helpers::DirectoryFinder directory_finder_;
  int image_counter_;
  LandmarkFinder landmark_finder_;
  std::chrono::time_point<std::chrono::system_clock> last_print_time_;
};

}  // namespace poker

#endif  // TRAINING_GAME_CONTROLLER_H_
