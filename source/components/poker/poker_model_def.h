#ifndef POKER_MODEL_DEF_H_
#define POKER_MODEL_DEF_H_

#include <string>

#include "libraries/model_generator/poker_model_generator/card_def.h"

namespace image_recognition {
namespace poker {

// template image names
const std::string kPlayer = "player";
const std::string kOponent = "oponent";
const std::string kAceClubs = "ace_clubs";

/// @class PokerModel
/// Entity
/// Contains the PokerModel
struct PokerModel {
  int total_players;
  int active_players;  // players currently in the hand
  bool in_hand;

  TableState table;
};

}  // poker
}  // namespace image_recognition

#endif  // POKER_MODEL_DEF_H_
