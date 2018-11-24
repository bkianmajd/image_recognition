#ifndef LANDMARK_CONFIG_DEF_H_
#define LANDMARK_CONFIG_DEF_H_

#include <vector>

#include "components/image_recognition/image_recognition_defs.h"
#include "libraries/screenshot_creator/screenshot_creator.h"

namespace poker {

enum Landmark {
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
  bool is_search = false;
  template_recognition::ScreenArea left_card;
  template_recognition::ScreenArea right_card;
};

// This returns the x and y location of the template image relative to the map
struct LandmarkResponseData {
  image_recognition::Point left_card;
  image_recognition::Point right_card;
};

using LandmarkRequestDataArray = std::array<LandmarkRequestData, LANDMARK_SIZE>;
using LandmarkResponseDataArray =
    std::array<LandmarkResponseData, LANDMARK_SIZE>;

constexpr int kDefaultWidth = 62;
constexpr int kDefaultHeight = 27;

}  // namespace poker

#endif  // LANDMARK_CONFIG_DEF_H_
