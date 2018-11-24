#ifndef SIX_PLAYER_CONFIG_H_
#define SIX_PLAYER_CONFIG_H_

#include "components/poker/poker_game_controller/definitions/landmark_config_def.h"

namespace poker {
namespace {}  // namespace

LandmarkRequestDataArray GenerateSixPlayerConfig() {
  LandmarkRequestDataArray data_array;
  LandmarkRequestData landmark_request_data;
  for (int i = 0; i < LANDMARK_SIZE; ++i) {
    Landmark landmark = static_cast<Landmark>(i);
    landmark_request_data.is_search = true;
    switch (landmark) {
      case LANDMARK_PLAYER_ZERO:
        landmark_request_data.left_card = template_recognition::ScreenArea(
            457, 431, kDefaultWidth, kDefaultHeight);
        landmark_request_data.right_card = template_recognition::ScreenArea(
            523, 431, kDefaultWidth, kDefaultHeight);
        break;
      case LANDMARK_PLAYER_ONE:
        landmark_request_data.left_card = template_recognition::ScreenArea(
            68, 322, kDefaultWidth, kDefaultHeight);
        landmark_request_data.right_card = template_recognition::ScreenArea(
            133, 322, kDefaultWidth, kDefaultHeight);
        break;
      case LANDMARK_PLAYER_TWO:
        landmark_request_data.left_card = template_recognition::ScreenArea(
            68, 97, kDefaultWidth, kDefaultHeight);
        landmark_request_data.right_card = template_recognition::ScreenArea(
            133, 97, kDefaultWidth, kDefaultHeight);
        break;
      case LANDMARK_PLAYER_THREE:
        landmark_request_data.left_card = template_recognition::ScreenArea(
            458, 11, kDefaultWidth, kDefaultHeight);
        landmark_request_data.right_card = template_recognition::ScreenArea(
            523, 13, kDefaultWidth, kDefaultHeight);
        break;
      case LANDMARK_PLAYER_FOUR:
        landmark_request_data.left_card = template_recognition::ScreenArea(
            851, 98, kDefaultWidth, kDefaultHeight);
        landmark_request_data.right_card = template_recognition::ScreenArea(
            915, 99, kDefaultWidth, kDefaultHeight);
        break;
      case LANDMARK_PLAYER_FIVE:
        landmark_request_data.left_card = template_recognition::ScreenArea(
            851, 324, kDefaultWidth, kDefaultHeight);
        landmark_request_data.right_card = template_recognition::ScreenArea(
            917, 324, kDefaultWidth, kDefaultHeight);
        break;
      default:
        // do not search for this landmark
        landmark_request_data.is_search = false;
    }

    data_array[i] = landmark_request_data;
  }
  return data_array;
}

}  // namespace poker

#endif  // SIX_PLAYER_CONFIG_H_
