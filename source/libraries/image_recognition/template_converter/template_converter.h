#ifndef TEMPLATE_CONVERTER_H_
#define TEMPLATE_CONVERTER_H_

#include <vector>

#include "libraries/image_recognition/image_recognition_defs.h"
#include "libraries/image_recognition/template_recognition/template_recognition_defs.h"

namespace recognition {

// Responsible for converting a template_recognition::Points to
// recognition::Point
class TemplateConverter {
 public:
  TemplateConverter();

  /// Converts a vector to a point by finding the best match
  Point Convert(const std::vector<ProbabilityPoint>& points);

 private:
  size_t GetLargestProbabilityIndex(const std::vector<ProbabilityPoint>& points);

  bool CheckVicinity(const ProbabilityPoint& point_1,
                     const ProbabilityPoint& point_2);

  Point ConvertToPoint(const ProbabilityPoint& point);
};

}  // namespace recognition

#endif  // TEMPLATE_CONVERTER_H_
