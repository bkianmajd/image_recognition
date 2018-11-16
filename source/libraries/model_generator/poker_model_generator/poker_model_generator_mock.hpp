#ifndef POKER_MODEL_GENERATOR_MOCK_H_
#define POKER_MODEL_GENERATOR_MOCK_H_

#include "components/image_recognition/image_recognition_api.h"
#include "libraries/model_generator/model_generator_interface.h"
#include "libraries/model_generator/poker_model_generator/poker_model_def.h"

namespace image_recognition {
namespace poker {

/// API to generate model
class PokerModelGeneratorMock : public ModelGeneratorInterface<PokerModel> {
 public:
  PokerModelGeneratorMock() {}

  /// Creates a specific landmark based on the string
  void AddLandmarkToModel(const Landmark& landmark) override {
      (void) landmark;
      // NO-OPT
  }

  const PokerModel& GenerateModel() override {
    poker_model_.active_players = 5;
    poker_model_.in_hand = true;
    poker_model_.table = TableState::TABLE_STATE_FLOP;
    poker_model_.total_players = 8;
    return poker_model_;
  }

 private:
  PokerModel poker_model_;
};

}  // poker
}  // namespace image_recognition

#endif  // POKER_MODEL_GENERATOR_MOCK_H_
