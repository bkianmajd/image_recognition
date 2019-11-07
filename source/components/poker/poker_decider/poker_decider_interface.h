#ifndef POKER_DECIDER_INTERFACE_H_
#define POKER_DECIDER_INTERFACE_H_

#include "components/poker/entities/game_model_def.h"

namespace poker {

enum DecisionType {
  DEC_UNKNOWN,
  DEC_FOLD,
  DEC_CHECK_FOLD,
  DEC_CHECK,
  DEC_CALL,
  DEC_RAISE,
};

struct Decision {
  DecisionType decisionType;
  double ammount = 0;
};

// High level API to decide what to do each hand
class PokerDeciderInterface {
 public:
  virtual ~PokerDeciderInterface() {}

  virtual Decision Deicide(const GameModel& gameModel,
                           const GameStatus& gameStatus) = 0;
};

}  // namespace poker

#endif  // POKER_DECIDER_INTERFACE_H_
