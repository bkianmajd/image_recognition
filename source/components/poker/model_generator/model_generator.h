#ifndef MODEL_GENERATOR_H_
#define MODEL_GENERATOR_H_

#include "components/poker/entities/game_model_def.h"

namespace poker {

// Holds persistance of the model such that it can do sanity checking or
// filtering
class ModelGenerator {
 public:
  ModelGenerator();

  const GameModel& GetGameModel() const;

  void Reset();

  // Table actions
  bool SetFlop(Card first_card, Card second_card, Card third_card);
  bool SetTurn(Card card);
  bool SetRiver(Card card);

  // Player Actions
  bool PlayerDeal(Card first_card, Card second_card);

 private:
  GameModel game_model_;
};

}  // namespace poker

#endif  // MODEL_GENERATOR_H_
