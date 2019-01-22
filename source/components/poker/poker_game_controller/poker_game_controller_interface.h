#ifndef POKER_GAME_CONTROLLER_INTERFACE_H_
#define POKER_GAME_CONTROLLER_INTERFACE_H_

#include <vector>

#include "components/poker/entities/game_model_def.h"

namespace poker {

// Converts images to decipher the workflow of a poker game
class PokerGameControllerInterface {
 public:
  PokerGameControllerInterface() = default;

  virtual ~PokerGameControllerInterface() = default;

  // Sets the data to process the image pipeline
  virtual void UpdateBigImage(const std::vector<char>& big_image_raw_data) = 0;
};

}  // namespace poker

#endif  // POKER_GAME_CONTROLLER_INTERFACE_H
