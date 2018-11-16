#ifndef TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_DEFS_
#define TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_DEFS_

namespace template_recognition {

// template id is a unique identifier
using TemplateId = int;

// x is along x axis - left side is 0
// y is along y axis - bottom is 0
struct Point {
  int x;
  int y;
  int template_match_type;
  double probability;
  bool isValid = true;
};

}  // namespace template_recognition

#endif  // TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_DEFS_
