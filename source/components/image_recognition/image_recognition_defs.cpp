#include "components/image_recognition/image_recognition_defs.h"

namespace image_recognition {

std::ostream& operator<<(std::ostream& os, const Point& point) {
  if (point.valid) {
    os << "true (";
  } else {
    os << "false (";
  }
  os << point.x << "," << point.y << ")";
  return os;
}

}  // image_recognition
