#ifndef IMAGE_RECOGNITION_DEFS_H_
#define IMAGE_RECOGNITION_DEFS_H_

#include <iostream>

namespace recognition {

struct Point {
  int x;  // pixel location
  int y;  // pixel location
  bool valid = false;
};

std::ostream& operator<<(std::ostream& os, const Point& point);

}  // namespace recognition

#endif  // IMAGE_RECOGNITION_DEFS_H_
