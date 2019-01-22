#ifndef PLAYER_LOCATION_DEF_H_
#define PLAYER_LOCATION_DEF_H_

namespace poker {

enum PlayerLocation {
  PLAYERLOC_PLAYER_ZERO = 0,  // This is yourself
  PLAYERLOC_PLAYER_ONE,       // Counter-clockwise from self
  PLAYERLOC_PLAYER_TWO,
  PLAYERLOC_PLAYER_THREE,
  PLAYERLOC_PLAYER_FOUR,
  PLAYERLOC_PLAYER_FIVE,
  PLAYERLOC_PLAYER_SIX,
  PLAYERLOC_PLAYER_SEVEN,
  PLAYERLOC_PLAYER_EIGHT,
  PLAYERLOC_PLAYER_NINE,
  PLAYERLOC_MAXSIZE,
};

enum ChairStatus {
  CHAIR_STATUS_UNKNOWN = 0,
  CHAIR_STATUS_EMPTY,
  CHAIR_STATUS_OUT,
  CHAIR_STATUS_OCCUPIED,
};

// The cards dealt by the dealer
enum DealerLocation {
  // Technically should never be called
  DEALER_NONE = 0,
  // The first three is the flop
  DEALER_ONE,
  DEALER_TWO,
  DEALER_THREE,
  // This is the turn
  DEALER_FOUR,
  // This is the river
  DEALER_FIVE,
  DEALER_MAX_SIZE,
};

}  // poker

#endif  // PLAYER_LOCATION_DEF_H_
