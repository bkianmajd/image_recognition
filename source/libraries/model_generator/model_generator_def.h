#ifndef MODEL_DEF_H_
#define MODEL_DEF_H_

#include "components/image_recognition/image_recognition_api.h"

namespace image_recognition {

struct Landmark {
  std::string image_name;
  int x_pixel;
  int y_pixel;
};

struct SimpleModel {
  std::vector<Landmark> landmark_locations_;
};

}  // namespace image_recognition

#endif  // MODEL_DEF_H_
