#ifndef LANDMARK_CONFIG_H_
#define LANDMARK_CONFIG_H_

#include <vector>

#include "libraries/screenshot_creator/screenshot_creator.h"

namespace poker {

enum LANDMARK {
  LANDMARK_PLAYER_ZERO = 0,  // This is yourself
  LANDMARK_PLAYER_ONE,       // Counter-clockwise from self
  LANDMARK_PLAYER_TWO,
  LANDMARK_PLAYER_THREE,
  LANDMARK_PLAYER_FOUR,
  LANDMARK_PLAYER_FIVE,
  LANDMARK_PLAYER_SIX,
  LANDMARK_PLAYER_SEVEN,
  LANDMARK_PLAYER_EIGHT,
  LANDMARK_PLAYER_NINE,
  LANDMARK_SIZE,
};

struct LandmarkRequestData {
  bool valid = false;
  std::string big_image_name;
};

struct LandmarkResponseData {
  bool found = false;
  std::string template_image;
};

using LandmarkRequestDataArray = std::array<LandmarkRequestData, LANDMARK_SIZE>;
using LandmarkResponseDataArray =
    std::array<LandmarkResponseData, LANDMARK_SIZE>;

}  // namespace poker

#endif  // LANDMARK_CONFIG_H_
