#ifndef POKER_MODEL_GENERATOR_H_
#define POKER_MODEL_GENERATOR_H_

#include "components/image_recognition/image_recognition_api.h"
#include "libraries/model_generator/model_generator_interface.h"
#include "libraries/model_generator/poker_model_generator/poker_model_def.h"

namespace image_recognition {
namespace poker {

/// API to generate model
class PokerModelGenerator : public ModelGeneratorInterface<PokerModel> {
 public:
  PokerModelGenerator() {}

  ~PokerModelGenerator() = default;

  /// Creates a specific landmark based on the string
  void AddLandmarkToModel(const Landmark& landmark) override;

  const PokerModel& GenerateModel() override;

 private:
  void Reset();
  void HandlePlayer(int loc_x, int loc_y);

  std::vector<Landmark> landmarks_;
  PokerModel poker_model_;
};

}  // namespace poker
}  // namespace image_recognition

#endif  // POKER_MODEL_GENERATOR_H_
