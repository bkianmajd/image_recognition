#include "components/poker/poker_game_controller/poker_landmark_generator/indicator_finder.h"

namespace poker {
namespace {
const std::string kTemplateDirectory =
    "components/poker/poker_game_controller/poker_landmark_generator/"
    "template_directory";

const std::string kSessionDirectory =
    "components/poker/poker_game_controller/poker_landmark_generator/"
    "indicator_session_directory";

const std::string kLandmarkName = "landmark.jpg";

constexpr helpers::DirectoryFinder::ReferenceFrame kRelativePath =
    helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace;

}  // namespace

IndicatorFinder::IndicatorFinder()
    : image_recognition_api_(
          helpers::DirectoryFinder(kTemplateDirectory, kRelativePath),
          helpers::DirectoryFinder(kSessionDirectory, kRelativePath)) {}

bool IndicatorFinder::FindIndicator(const std::vector<char>& big_raw_image,
                                    int* x_indicator, int* y_indicator) {
  image_recognition_api_.SetBigImage(big_raw_image);
  image_recognition::Point point =
      image_recognition_api_.TemplateMatch(kLandmarkName);
  *x_indicator = point.x;
  *y_indicator = point.y;
  return point.valid;
}

}  // namespace poker
