#ifndef MODEL_GENERATOR_MOCK_H_
#define MODEL_GENERATOR_MOCK_H_

#include "components/image_recognition/image_recognition_api.h"
#include "libraries/model_generator/model_generator_interface.h"

namespace image_recognition {

/// API to generate model
class ModelGeneratorMock : public ModelGeneratorInterface<SimpleModel> {
 public:
  ModelGeneratorMock();

  /// Creates a specific landmark based on the string
  void AddLandmarkToModel(Landmark* landmark) override {}

  SimpleModel GenerateModel(BigImage) override {}

 private:
};

}  // namespace image_recognition

#endif  // MODEL_GENERATOR_MOCK_H_
