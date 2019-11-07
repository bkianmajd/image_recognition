#ifndef SIMPLE_DECIDER_H_
#define SIMPLE_DECIDER_H_

#include "components/poker/poker_decider/poker_decider_interface.h"
#include "components/poker/statistics/hand_calculator/hand_calculator.h"

namespace poker {

class SimpleDecider : public PokerDeciderInterface {
 public:
  SimpleDecider();
  ~SimpleDecider() override = default;

  Decision Deicide(const GameModel& gameModel,
                   const GameStatus& gameStatus) override {

  }

 private:
  statistics::HandCalculator hand_calculator_;
};

}  // namespace poker

#endif  // SIMPLE_DECIDER_H_
