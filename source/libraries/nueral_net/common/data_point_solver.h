#ifndef DATA_POINT_SOLVER_H_
#define DATA_POINT_SOLVER_H_

#include <cmath>
#include <iostream>
#include <vector>

#include "libraries/nueral_net/common/layer.h"
#include "libraries/nueral_net/common/sigmoid.h"
#include "libraries/nueral_net/defs/nueral_net_defs.h"

// Put this in the cpp file of layer
#include "eigen3/Eigen/Dense"

namespace ml {
using ThetaGradient = Eigen::MatrixX<float>;

struct SingleDataPointResult {
  float cost_without_regularization = 0;
  std::vector<ThetaGradient> gradients_without_regularization;
};

class DataPointSolver {
 public:
  DataPointSolver(const Layer& input_layer, const std::vector<Theta>& thetas,
                  const Layer& output_layer)
      : num_layers_(thetas.size() + 1),
        input_layer_(input_layer),
        thetas_(thetas),
        output_layer_(output_layer) {
    layers_with_sigmoid_.resize(num_layers_);
    layers_without_sigmoid_.resize(num_layers_);
    costs_.resize(num_layers_);
  }

  SingleDataPointResult Solve() {
    SingleDataPointResult result;

    ForwardPropogate();
    result.cost_without_regularization = CalculateUnregularizedCost();

    BackPropogate();
    result.gradients_without_regularization = SolveForThetaGradients();

    return result;
  }

 private:
  using Cost = Eigen::VectorX<float>;

  float CalculateUnregularizedCost() const {
    const Layer& estimated_output_layer = layers_with_sigmoid_[num_layers_ - 1];
    const long output_size = output_layer_.Size();

    float total_cost = 0;
    // Output layer is the actual output. Its either a zero or a one
    for (int i = 0; i < output_size; ++i) {
      float cost =
          (-1.0f * output_layer_.At(i) * logf(estimated_output_layer.At(i))) -
          ((1.0f - output_layer_.At(i)) *
           logf(1.0f - estimated_output_layer.At(i)));
      assert(cost >= 0);
      total_cost += cost;
    }
    return total_cost;
  }

  // Updates |layers_with_sigmoid_|, |layers_without_sigmoid_|
  void ForwardPropogate() {
    layers_with_sigmoid_[0] = input_layer_;
    layers_without_sigmoid_[0] = input_layer_;

    for (size_t i = 1; i < num_layers_; ++i) {
      layers_without_sigmoid_[i] =
          layers_with_sigmoid_[i - 1].ForwardPropogate(thetas_[i - 1]);

      layers_with_sigmoid_[i] = layers_without_sigmoid_[i].CalculateSigmoid();
    }
  }

  // Updates |costs_|
  void BackPropogate() {
    const Layer& estimated_output_layer = layers_with_sigmoid_[num_layers_ - 1];
    costs_[num_layers_ - 1] =
        estimated_output_layer.Get() - output_layer_.Get();

    // Ignore the zeroth index
    for (size_t i = num_layers_ - 2; i > 0; --i) {
      Eigen::VectorX<float> sig_grad =
          SigmoidGradient(layers_without_sigmoid_[i].GetWithBias());
      Eigen::VectorX<float> back_propogation =
          thetas_[i].Get().transpose() * costs_[i + 1];

      // Theta2' * cost_3 .* sigmoid_gradient(layer2)
      Eigen::VectorX<float> cost = back_propogation.cwiseProduct(sig_grad);

      // need to remove the bias here (2:end)
      costs_[i].resize(cost.size() - 1);
      for (int j = 0; j < costs_[i].size(); ++j) {
        costs_[i](j) = cost(j + 1);
      }
    }
  }

  // Size is size(|theta_|)
  std::vector<ThetaGradient> SolveForThetaGradients() const {
    std::vector<ThetaGradient> result;
    result.resize(thetas_.size());
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] =
          costs_[i + 1] * layers_with_sigmoid_[i].GetWithBias().transpose();
    }
    return result;
  }

  const size_t num_layers_;
  const Layer input_layer_;
  const std::vector<Theta> thetas_;
  const Layer output_layer_;

  // num_layers = size(|theta_|) + 1
  // layer 0 is input layer, layer[n-1] is output layer
  std::vector<Layer> layers_with_sigmoid_;
  std::vector<Layer> layers_without_sigmoid_;

  // Size is |num_layers_|, zero index is not used
  std::vector<Cost> costs_;
};

}  // namespace ml

#endif  // DATA_POINT_SOLVER_H_
