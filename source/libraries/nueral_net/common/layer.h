#ifndef LAYER_H_
#define LAYER_H_

#include <cmath>
#include <vector>

#include "libraries/nueral_net/common/sigmoid.h"
#include "libraries/nueral_net/common/theta_creator.h"

// Put this in the cpp file of layer
#include "eigen3/Eigen/Dense"

namespace ml {

// A layer consists of 1 row by m columns
class Layer {
 public:
  // Convert an input / output layer into a generic layer
  Layer(const std::vector<float>& data) {
    if (data.empty()) {
      return;
    }

    // resize layers
    layer_.resize(static_cast<int>(data.size()));
    layer_with_bias_.resize(static_cast<int>(data.size() + 1));

    // fill in data
    layer_with_bias_(0) = 1;
    for (size_t i = 0; i < data.size(); ++i) {
      layer_(static_cast<int>(i)) = data[i];
      layer_with_bias_(static_cast<int>(i + 1)) = data[i];
    }
  }

  Layer(const Eigen::VectorX<float>& data) {
    if (data.size() == 0) {
      return;
    }

    // resize layers
    layer_with_bias_.resize(data.size() + 1);

    // fill in data
    layer_with_bias_(0) = 1;
    for (int i = 0; i < data.size(); ++i) {
      layer_with_bias_(i + 1) = data(i);
    }

    layer_ = data;
  }

  Layer() {}

  float At(int i) const { return layer_(i); }

  long Size() const { return layer_.size(); }

  const Eigen::VectorX<float>& Get() const { return layer_; }
  const Eigen::VectorX<float>& GetWithBias() const { return layer_with_bias_; }

  Layer ForwardPropogate(const Theta& theta) const {
    Eigen::VectorX<float> new_layer =
        theta.Get() * (layer_with_bias_);
    return Layer(new_layer);
  }

  Layer CalculateSigmoid() const { return Layer(Sigmoid(layer_)); }

 private:
  Eigen::VectorX<float> layer_;
  Eigen::VectorX<float> layer_with_bias_;
};

}  // namespace ml

#endif  // LAYER_H_
