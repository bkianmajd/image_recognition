#ifndef POKER_LANDMARK_GENERATOR_H_
#define POKER_LANDMARK_GENERATOR_H_

#include <vector>

#include "libraries/image_recognition/image_recognition_api.h"
#include "components/poker/poker_game_controller/definitions/landmark_config_def.h"
#include "helpers/directory_finder.h"
#include "libraries/model_generator/model_generator_def.h"

namespace poker {

/// Generates a landmark relative to a marked indicator
/// Essentially converts screenshot areas to points on a predefined map
/// It does this by taking a series of screenshots relative to that indicator.
/// The caller must know what the indicator is and correctly match it before
/// calling Generate()
class PokerLandmarkGenerator {
 public:
  explicit PokerLandmarkGenerator(
      const LandmarkRequestDataArray& landmark_request_data_array);

  LandmarkResponseDataArray GenerateRelativeToIndicator(
      const std::vector<char>& screenshot, int x_indicator, int y_indicator);

 private:
  recognition::Point ConvertToPoint(
      const template_recognition::ScreenArea& screen_area, int x_indicator,
      int y_indicator);

  const LandmarkRequestDataArray landmark_request_data_array_;
  recognition::ImageRecognitionApi image_recognition_api_;

  // For getting template images
  template_recognition::ScreenshotCreator screenshot_creator_;
};

}  // namespace poker

#endif  // POKER_LANDMARK_GENERATOR_H_
