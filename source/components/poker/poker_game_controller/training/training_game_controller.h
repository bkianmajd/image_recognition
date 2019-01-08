#ifndef TRAINING_GAME_CONTROLLER_H_
#define TRAINING_GAME_CONTROLLER_H_

#include <chrono>
#include <vector>

#include "components/poker/poker_game_controller/landmark_finder/landmark_finder.h"
#include "components/poker/poker_game_controller/landmark_finder/player_locator/player_locator.h"
#include "components/poker/poker_game_controller/landmark_finder/table_locator/table_locator.h"
#include "components/poker/poker_game_controller/poker_game_controller_interface.h"
#include "helpers/directory_finder.h"
#include "libraries/image_def/image_def.h"
#include "libraries/image_pipeline/pipeline.h"
#include "libraries/image_trainer/trainer.h"
#include "libraries/screenshot_creator/screenshot_creator.h"

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
  void RecordCards(const std::vector<char>& big_image_raw_data);
  void TakeScreenshots(const std::vector<char>& big_image_raw_data);
  void ReadCards(const std::vector<char>& big_image_raw_data);

  // Return true if the card was recognized already
  bool AddCardToTrainer(const image::Image& image);

  helpers::DirectoryFinder directory_finder_;
  int image_counter_;
  LandmarkFinder landmark_finder_;

  // For recording cards
  template_recognition::ScreenshotCreator screenshot_creator_;
  TableLocator table_locator_;
  std::vector<PlayerLocator> player_locator_;
  image::Pipeline pipeline_;
  image::Trainer trainer_;
  std::chrono::time_point<std::chrono::system_clock> last_print_time_;
};

}  // namespace poker

#endif  // TRAINING_GAME_CONTROLLER_H_
