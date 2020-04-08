#ifndef NUERAL_NET_H_
#define NUERAL_NET_H_

#include <cassert>
#include <iostream>
#include <vector>

#include "libraries/nueral_net/common/layer.h"
#include "libraries/nueral_net/common/sigmoid.h"
#include "libraries/nueral_net/common/theta_creator.h"

// Put this in the cpp file of layer
#include <gtest/gtest_prod.h>
#include "eigen3/Eigen/Dense"
#include "libraries/nueral_net/common/data_point_solver.h"

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

    // TODO: Assert the EnumType max value is equal to the (output size - 1)
  }

  void AddDataSet(const InputLayer& input_layer, EnumType classifier) {
    assert(input_layer.size() == nueral_net_def_.input_size);
    // Convert input layer to a Layer
    input_layers_.emplace_back(input_layer);

    // Convert the clasifier to a layer
    output_layers_.push_back(Convert(classifier));
  }

  NueralNetResult Train() {
    NueralNetResult nueral_net_result;
    nueral_net_result.nueralNetDef = nueral_net_def_;

    int m_data_points = input_layers_.size();
    if (m_data_points == 0) {
      return nueral_net_result;
    }

    std::pair<Cost, Gradient> cost_and_gradient = SolveCostFunction();

    std::cout << "Cost: " << cost_and_gradient.first << std::endl;

    // Solve for the new theta using gradient desent..expect the cost to reduce
    // Gradient desent: New = Old - Gradient*Old
    // Rasterize solve this with a tripple for loop
    float slope = 0;
    for (size_t layerIndex = 0; layerIndex < thetas_.size(); ++layerIndex) {
      const ThetaGradient& thetaGraidnet = cost_and_gradient.second[layerIndex];
      for (int i = 0; i < thetaGraidnet.rows(); ++i)
        for (int j = 0; j < thetaGraidnet.cols(); ++j) {
          slope = thetaGraidnet(i, j) * thetaGraidnet(i, j);
        }
    }
    // Now find the step - initial step is 1  / (1 - slope)
    slope = -1 * slope;
    float step = 1.0f / (1.0f - slope);

    // Solve for the next theta:
    // New theta = old_theta - step * gradient
    for (size_t layerIndex = 0; layerIndex < thetas_.size(); ++layerIndex) {
      Theta& theta = thetas_[layerIndex];
      const ThetaGradient& thetaGraidnet = cost_and_gradient.second[layerIndex];
      theta.GetMutable() = theta.Get() - step * thetaGraidnet;
    }

    return nueral_net_result;
  }

 private:
  FRIEND_TEST(NueralNetTest, TestNueralNet);
  using Cost = float;
  using Gradient = std::vector<ThetaGradient>;

  // Converts the classifier to an output layer of all zeros, but one 1
  Layer Convert(EnumType classifier) const {
    std::vector<float> output_layer(nueral_net_def_.output_size, 0.0);

    // Convert the clasifier to an integer. It is assumed clasifiers always
    // start at 0, and are contigious
    size_t index = static_cast<size_t>(classifier);
    assert(index < nueral_net_def_.output_size);

    output_layer[index] = 1.0;
    return Layer{output_layer};
  }

  std::pair<Cost, Gradient> SolveCostFunction() const {
    // Solve for the nueral net result - zero the data
    SingleDataPointResult aggregate_result;
    DataPointSolver solver(input_layers_[0], thetas_, output_layers_[0]);
    aggregate_result = solver.Solve();

    int m_data_points = input_layers_.size();
    for (int i = 1; i < m_data_points; ++i) {
      DataPointSolver solver(input_layers_[i], thetas_, output_layers_[i]);
      SingleDataPointResult result = solver.Solve();
      // sum the total costs without the regularization term
      aggregate_result.cost_without_regularization =
          aggregate_result.cost_without_regularization +
          result.cost_without_regularization;

      // sum the total gradients, which are vectors of matricies
      for (size_t g_index = 0;
           g_index < aggregate_result.gradients_without_regularization.size();
           ++g_index) {
        aggregate_result.gradients_without_regularization[g_index] =
            aggregate_result.gradients_without_regularization[g_index] +
            result.gradients_without_regularization[g_index];
      }
    }

    // divide the sum/aggregate over the total size (m_data_points) but not
    // for the gradient yet
    aggregate_result.cost_without_regularization =
        aggregate_result.cost_without_regularization / m_data_points;

    // Add the reguliarization term - these results now have regularization
    aggregate_result.cost_without_regularization =
        aggregate_result.cost_without_regularization +
        CalculateCostRegularizationTerm();

    // The gradient regularization term is term is updated by passing a
    // pointer to the variable without reguarlizatoin
    UpdateGradientWithRegularization(
        &aggregate_result.gradients_without_regularization);

    // Divide the total gradients by m to take the average
    for (size_t g_index = 0;
         g_index < aggregate_result.gradients_without_regularization.size();
         ++g_index) {
      aggregate_result.gradients_without_regularization[g_index] =
          aggregate_result.gradients_without_regularization[g_index] /
          m_data_points;
    }

    return std::pair<Cost, Gradient>{
        aggregate_result.cost_without_regularization,
        aggregate_result.gradients_without_regularization};
  }

  //
  void UpdateGradientWithRegularization(
      std::vector<ThetaGradient>* gradients) const {
    int m_data_set_size = input_layers_.size();
    const float lambda_regularization_coefficient = 1;

    // Each gradient should be the same size as theta
    // Multiply lambda to theta and add that to the gradient
    for (size_t g_index = 0; g_index < gradients->size(); ++g_index) {
      for (int i = 0; i < gradients->at(g_index).rows(); ++i) {
        // Skip the first column (j starts at 1)
        for (int j = 1; j < gradients->at(g_index).cols(); ++j) {
          auto gradient_term =
              lambda_regularization_coefficient * thetas_[g_index].Get()(i, j);
          gradients->at(g_index)(i, j) =
              gradient_term + gradients->at(g_index)(i, j);
        }
      }
    }
  }

  float CalculateCostRegularizationTerm() const {
    // Now find the cost with regularization of theta values
    constexpr float lambda_regularization_coefficient = 1;
    // Skip the first column of theta to avoid regularizing the theta values
    // associated with the bias
    constexpr int skip_col = 0;

    // We are summing each individual value of theta except for the bias
    int m_data_set_size = input_layers_.size();
    float total_theta_cost = 0;
    for (size_t i = 0; i < thetas_.size(); ++i) {
      const Eigen::MatrixX<float>& matrix = thetas_.at(i).Get();
      for (int row = 0; row < matrix.rows(); ++row) {
        for (int col = 0; col < matrix.cols(); ++col) {
          if (col == skip_col) {
            continue;
          }
          total_theta_cost += matrix(row, col) * matrix(row, col);
        }
      }
    }
    float theta_regulate = lambda_regularization_coefficient *
                           total_theta_cost / (2 * m_data_set_size);
    return theta_regulate;
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

  const NueralNetDef nueral_net_def_;

  std::vector<Layer> input_layers_;
  std::vector<Layer> output_layers_;
  std::vector<Theta> thetas_;
};

}  // namespace ml

#endif  // NUERAL_NET_H_
