#include "components/poker/poker_game_controller/training/training_game_controller.h"

#include "helpers/file_manager/file_manager.h"

#include <string>

namespace poker {
namespace {

constexpr char kDefaultDirectory[] =
    "components/poker/poker_game_controller/training/ignore_images";

}  // namespace

TrainingGameController::TrainingGameController()
    : directory_finder_(
          kDefaultDirectory,
          helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
      image_counter_(0) {}

void TrainingGameController::UpdateBigImage(
    const std::vector<char>& big_image_raw_data) {
  std::stringstream ss;
  ss << image_counter_++ << ".jpg";
  // Store the file
  helpers::FileManager::StoreFile(
      big_image_raw_data.data(), big_image_raw_data.size(),
      directory_finder_.GetAbsPathOfTargetFile(ss.str()));
}

bool TrainingGameController::ProcessNextWorkflow(
    const GameStatus& game_status) {
  (void)game_status;
  return false;
}

}  // namespace poker
