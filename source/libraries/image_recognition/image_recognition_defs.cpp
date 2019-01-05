#include "libraries/image_recognition/image_recognition_defs.h"

namespace recognition {

std::ostream& operator<<(std::ostream& os, const Point& point) {
  if (point.valid) {
    os << "true (";
  } else {
    os << "false (";
  }
  os << point.x << "," << point.y << ")";
  return os;
}

}  // recognition
