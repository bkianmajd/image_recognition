#ifndef MODEL_GENERATOR_INTERFACE_H_
#define MODEL_GENERATOR_INTERFACE_H_

#include "libraries/image_recognition/image_recognition_api.h"
#include "libraries/model_generator/model_generator_def.h"

namespace image_recognition {

/// API to generate model
/// Any model can be generated, i.e. poker model, wow model, simple model
/// A model is generated from a series of landmarks.
template <typename Model>
class ModelGeneratorInterface {
 public:
  virtual ~ModelGeneratorInterface() = default;

  /// Creates a specific landmark based on the string
  virtual void AddLandmarkToModel(const Landmark& landmark) = 0;

  virtual const Model& GenerateModel() = 0;
};

}  // namespace image_recognition

#endif  // MODEL_GENERATOR_INTERFACE_H_
