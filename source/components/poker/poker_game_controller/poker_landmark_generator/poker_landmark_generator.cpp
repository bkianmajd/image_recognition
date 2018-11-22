#include "components/poker/poker_game_controller/poker_landmark_generator/poker_landmark_generator.h"

namespace poker {
namespace {
const std::string kTemplateDirectory =
    "components/poker/poker_game_controller/poker_landmark_generator/"
    "template_directory";

const std::string kSessionDirectory =
    "components/poker/poker_game_controller/poker_landmark_generator/"
    "landmark_session_directory";

constexpr helpers::DirectoryFinder::ReferenceFrame kRelativePath =
    helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace;

}  // namespace

PokerLandmarkGenerator::PokerLandmarkGenerator(
    const LandmarkRequestDataArray& landmark_request_data_array)
    : landmark_request_data_array_(landmark_request_data_array),
      session_directory_(kSessionDirectory, kRelativePath),
      image_recognition_api_(
          helpers::DirectoryFinder(kTemplateDirectory, kRelativePath),
          session_directory_) {}

const LandmarkResponseDataArray&
PokerLandmarkGenerator::GenerateRelativeToIndicator(
    const std::vector<char>& big_raw_image, int x_indicator, int y_indicator) {

  (void)big_raw_image;
  (void)x_indicator;
  (void)y_indicator;

  return landmark_response_data_array_;
}

}  // namespace poker
