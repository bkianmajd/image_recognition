#include "components/poker/poker_game_controller/poker_model_generator/poker_model_generator.h"

#include <iostream>

namespace image_recognition {
namespace poker {

void PokerModelGenerator::AddLandmarkToModel(const Landmark& landmark) {
  landmarks_.push_back(landmark);
}

const PokerModel& PokerModelGenerator::GenerateModel() {
  for (const Landmark& landmark : landmarks_) {
    if (landmark.image_name == kPlayer) {
      HandlePlayer(landmark.x_pixel, landmark.y_pixel);
      continue;
    }

    std::cout << "Could not handle " << landmark.image_name << std::endl;
  }

  return poker_model_;
}

void PokerModelGenerator::HandlePlayer(int loc_x, int loc_y) {
  poker_model_.active_players++;
  if (loc_x == 15 && loc_y == 15) {
    poker_model_.in_hand = true;
  }
}

void PokerModelGenerator::Reset() {
  poker_model_.active_players = 0;
  poker_model_.in_hand = false;
  poker_model_.table = poker::TABLE_STATE_PRE_FLOP;
  poker_model_.total_players = 10;
}

}  // namespace poker
}  // image_recognition
