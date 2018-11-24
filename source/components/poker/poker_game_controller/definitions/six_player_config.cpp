#ifndef SIX_PLAYER_CONFIG_H_
#define SIX_PLAYER_CONFIG_H_

#include "components/poker/poker_game_controller/definitions/landmark_config_def.h"

namespace poker {
namespace {

}  // namespace

LandmarkRequestDataArray GenerateSixPlayerConfig() {
  LandmarkRequestDataArray data_array;
  LandmarkRequestData landmark_request_data;
  for (int i = 0; i < LANDMARK_SIZE; ++i) {
    Landmark landmark = static_cast<Landmark>(i);
    landmark_request_data.is_search = true;
    switch (landmark) {
      case LANDMARK_PLAYER_ZERO:
        landmark_request_data.left_card = template_recognition::ScreenArea(
            457, 431, kDefaultCardWidth, kDefaultCardHeight);
        landmark_request_data.right_card = template_recognition::ScreenArea(
            523, 431, kDefaultCardWidth, kDefaultCardHeight);
        break;
      case LANDMARK_PLAYER_ONE:
        break;
      /*
case LANDMARK_PLAYER_TWO:
break;
case LANDMARK_PLAYER_THREE:
break;
case LANDMARK_PLAYER_FOUR:
break;
case LANDMARK_PLAYER_FIVE:
break;
*/
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
