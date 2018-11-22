#ifndef GAME_MODEL_DEF_H_
#define GAME_MODEL_DEF_H_

#include <string>
#include <vector>

#include "components/poker/entities/card_def.h"

namespace poker {

// template image names
const std::string kPlayer = "player";
const std::string kOponent = "oponent";
const std::string kAceClubs = "ace_clubs";

/// @struct GameModel
/// Entity
/// Contains the information for a single game
struct GameModel {
  int total_players;
  int active_players;  // players currently in the hand
  bool in_hand;

  TableState table;
};

}  // poker

#endif  // GAME_MODEL_DEF_H_
