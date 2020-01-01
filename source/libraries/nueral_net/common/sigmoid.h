#ifndef SIGMOID_H_
#define SIGMOID_H_

#include <cmath>

// Put this in the cpp file of layer
#include "eigen3/Eigen/Dense"

namespace ml {

inline Eigen::VectorX<float> Sigmoid(const Eigen::VectorX<float>& data) {
  //   g = 1.0 ./ (1.0 + exp(-z));
  Eigen::VectorX<float> result = data;

  for (int i = 0; i < result.size(); ++i) {
    float denom = std::exp(-1.0f * (result)(i));
    result(i) = 1.0f / (1.0f + denom);
  }
  return result;
}

inline Eigen::VectorX<float> SigmoidGradient(const Eigen::VectorX<float>& data) {
  // g'(z) = g(z) * (1 - g(z))
  // g(z) = sigmoid(z);

  // First find sigmoid(z)
  Eigen::VectorX<float> result = Sigmoid(data);

  for (int i = 0; i < result.size(); ++i) {
    result(i) = result(i) * (1.0f - result(i));
  }
  return result;
}

}  // namespace ml

#endif  // SIGMOID_H_
