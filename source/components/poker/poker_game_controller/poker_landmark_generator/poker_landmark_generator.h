#ifndef POKER_LANDMARK_GENERATOR_H_
#define POKER_LANDMARK_GENERATOR_H_

#include <vector>

#include "components/image_recognition/image_recognition_api.h"
#include "components/poker/poker_game_controller/definitions/landmark_config.h"
#include "helpers/directory_finder.h"
#include "libraries/model_generator/model_generator_def.h"

namespace poker {

/// Generates a landmark relative to a marked indicator
/// It does this by taking a series of screenshots relative to that indicator.
/// The caller must know what the indicator is and correctly match it before
/// calling Generate()
class PokerLandmarkGenerator {
 public:
  explicit PokerLandmarkGenerator(const LandmarkRequestDataArray& landmark_request_data_array);

  const LandmarkResponseDataArray& GenerateRelativeToIndicator(
      const std::vector<char>& big_raw_image, int x_indicator, int y_indicator);

 private:
  const LandmarkRequestDataArray landmark_request_data_array_;
  helpers::DirectoryFinder session_directory_;
  image_recognition::ImageRecognitionApi image_recognition_api_;

  LandmarkResponseDataArray landmark_response_data_array_;
};

}  // namespace poker

#endif  // POKER_LANDMARK_GENERATOR_H_
