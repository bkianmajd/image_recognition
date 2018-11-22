#ifndef INDICATOR_FINDER_H_
#define INDICATOR_FINDER_H_

#include <vector>

#include "components/image_recognition/image_recognition_api.h"
#include "helpers/directory_finder.h"
#include "libraries/model_generator/model_generator_def.h"

namespace poker {

/// Finds the indicator from a big image
class IndicatorFinder {
 public:
  IndicatorFinder();

  bool FindIndicator(const std::vector<char>& big_raw_image, int* x_indicator,
                     int* y_indicator);

 private:
  image_recognition::ImageRecognitionApi image_recognition_api_;
};

}  // namespace poker

#endif  // INDICATOR_FINDER_H_
