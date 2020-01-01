#ifndef NUERAL_NET_H_
#define NUERAL_NET_H_

#include <cassert>
#include <iostream>
#include <vector>

#include "libraries/nueral_net/common/sigmoid.h"
#include "libraries/nueral_net/common/theta_creator.h"
#include "libraries/nueral_net/common/layer.h"

// Put this in the cpp file of layer
#include "eigen3/Eigen/Dense"

namespace ml {

using InputLayer = std::vector<float>;

struct Output {};

class Gradient {
 public:
 private:
};

//! The enum type needs to be ranked zero to n
template <typename EnumType>
class NueralNetTrainer {
 public:
  NueralNetTrainer(NueralNetDef nueral_net_def)
      : nueral_net_def_(nueral_net_def) {
    assert(nueral_net_def_.hidden_layers.size() > 0);
    thetas_ = CreateThetas(nueral_net_def);
  }

  void AddDataSet(const InputLayer& input_layer, EnumType classifier) {
    assert(input_layer.size() == nueral_net_def_.input_size);
    input_layers_.push_back(input_layer);
    output_layers_.push_back(classifier);
  }

  NueralNetResult Train() {
    NueralNetResult result;
    result.nueralNetDef = nueral_net_def_;

    // Sum the regularization term to the average cost without
    // regularization to get the final result
    float regularized_cost = CalculateCostRegularizationTerm() +
                             CalculateAverageCostWithoutRegularization();

    // Get the gradient
    std::vector<Gradient> CalculateGradient();

    return NueralNetResult();
  }

 private:
  float CalculateCostRegularizationTerm() const {
    // Now find the cost with regularization of theta values
    constexpr float lambda_regularization_coefficient = 1;
    // Skip the first column of theta to avoid regularizing the theta values
    // associated with the bias
    constexpr int skip_col = 0;

    int m_data_set_size = input_layers_.size();
    float total_theta_cost = 0;
    for (int i = 0; i < thetas_.size(); ++i) {
      const Eigen::MatrixX<float>& matrix = thetas_.at(i).Get();
      for (int row = 0; row < matrix.rows(); ++row) {
        for (int col = 0; col < matrix.cols(); ++col) {
          if (col == skip_col) {
            continue;
          }
          total_theta_cost += matrix(row, col);
        }
      }
    }
    float theta_regulate = lambda_regularization_coefficient *
                           total_theta_cost / (2 * m_data_set_size);
    return theta_regulate;
  }

  float CalculateAverageCostWithoutRegularization() const {
    int m_data_set_size = input_layers_.size();
    float total_cost = 0;
    for (int i = 0; i < m_data_set_size; ++i) {
      // Forward propogate to calculated the output layer
      Layer& inputLayer = input_layers_[i];
      Layer estimated_output_layer = ForwardPropogation(inputLayer);

      // Apply clasification to get the actual output layer
      EnumType outputClasifier = output_layers_[i];
      Layer actual_output_layer =
          GetActualOutputLayerFromClasifier(outputClasifier);

      // Now calculate the cost between the estimated output vs the actual
      // output layer
      total_cost += CalculateCostForSingleDataSet(actual_output_layer,
                                                  estimated_output_layer);
    }

    // Average the total cost
    float average_cost_without_regularization = total_cost / m_data_set_size;
    return average_cost_without_regularization;
  }

  float CalculateCostForSingleDataSet(
      const Layer& actual_output_layer,
      const Layer& estimated_output_layer) const {
    assert(actual_output_layer.Size() == estimated_output_layer.Size());
    assert(actual_output_layer.Size() == nueral_net_def_.output_size);

    float total_cost = 0;
    for (int i = 0; i < nueral_net_def_.output_size; ++i) {
      float cost = (-1 * actual_output_layer.At(i) *
                    log10f(estimated_output_layer.At(i))) -
                   ((1.0f - actual_output_layer.At(i)) *
                    log10f(1.0f - estimated_output_layer.At(i)));
      assert(cost > 0);
      total_cost += cost;
    }
    return total_cost;
  }

  // Here we assume the EnumType starts at zero.
  Layer GetActualOutputLayerFromClasifier(EnumType output_clasifier) const {
    std::vector<float> output_layer;
    output_layer.resize(nueral_net_def_.output_size);
    // Layer output_layer;
    size_t index = static_cast<int>(output_clasifier);

    // Set the output clasifier equal to one...all other indicies are zero
    output_layer[index] = 1;
    return Layer(output_layer);
  }

  Layer ForwardPropogation(const Layer& inputLayer) const {
    if (input_layers_.empty()) {
      std::cerr << "Should technically never be called" << std::endl;
      return Layer();
    }

    Layer layer = inputLayer.ForwardPropogate(thetas_[0]);
    layer.ApplySigmoid();

    // Proceed to find the rest of the layers
    for (size_t i = 1; i < nueral_net_def_.hidden_layers.size(); ++i) {
      layer = layer.ForwardPropogate(thetas_[i]);

      // Use the sigmoid to calculate the new activation function
      layer = layer.ApplySigmoid();
    }

    return layer;
  }

  // The zeroth index is the input layer
  std::vector<Gradient> CalculateGradient(
      const std::vector<Layer>& layers_without_sigmoid,
      const std::vector<Layer>& layers_with_sigmoid) const {
    // Create the gradients
    std::vector<Gradient> gradients;
    gradients.resize(thetas_.size());

    if (gradients.size() == 0) {
      return gradients;
    }

    // Calculate the cost
    Eigen::VectorX<float> last_cost;

    // Run backward propogation
    for (int i = gradients.size() - 1; i >= 0; --i) {
      // Calculate the gradient, ends at 0 which is the gradient of the input layer
      gradients[i].Solve(last_cost, layers_without_sigmoid[i].GetWithBias());

      last_cost = thetas_[i] * last_cost*SigmoidGradient(layers_without_sigmoid)
    }
  }

  const NueralNetDef nueral_net_def_;

  std::vector<InputLayer> input_layers_;
  std::vector<EnumType> output_layers_;
  std::vector<Theta> thetas_;
};

}  // namespace ml

#endif  // NUERAL_NET_H_
