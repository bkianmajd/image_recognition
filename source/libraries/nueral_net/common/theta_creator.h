#ifndef THETA_CREATOR_H_
#define THETA_CREATOR_H_

#include <cmath>
#include <vector>

#include "libraries/nueral_net/defs/nueral_net_defs.h"

// Put this in the cpp file of layer
#include "eigen3/Eigen/Dense"

namespace ml {

inline float RandomFloat(float a, float b) {
  float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  float diff = b - a;
  float r = random * diff;
  return a + r;
}

class Theta {
 public:
  Theta(Eigen::MatrixX<float> matrix) : matrix_(matrix) {}
  const Eigen::MatrixX<float>& Get() const { return matrix_; }
  Eigen::MatrixX<float>& GetMutable() { return matrix_; }

 private:
  Eigen::MatrixX<float> matrix_;
};


void RandomizeThetas(std::vector<Theta>* thetas) {
  constexpr float range = 0.12f;
  for (size_t i = 0; i < thetas->size(); ++i) {
    Eigen::MatrixX<float>& matrix = thetas->at(i).GetMutable();
    for (int row = 0; matrix.rows(); ++row) {
      for (int col = 0; matrix.cols(); ++col) {
        matrix(row, col) = RandomFloat(-range, range);
      }
    }
  }
}

std::vector<Theta> CreateThetas(const NueralNetDef& nueral_net_def) {
  std::vector<Theta> thetas;
  // Solve for the theta to get you to the next hidden layer row size
  // i.e. Theta * X = Hidden Layer
  int previous_layer = static_cast<int>(nueral_net_def.input_size);
  for (std::size_t i = 0; i < nueral_net_def.hidden_layers.size(); ++i) {
    int cols = previous_layer + 1;
    int rows = nueral_net_def.hidden_layers[i];
    Eigen::MatrixX<float> matrix;
    matrix.resize(rows, cols);
    thetas.push_back(std::move(matrix));

    // Theta[row_1 x col_1] * X[row_2 x 1] = [row_1 x 1]
    // Therefore the new layer is of size [row_1 x 1]
    previous_layer = rows;
  }

  // Now find the last theta to get to the size of the output layer
  // i.e. Theta * Last Hidden Layer = Output layer
  int rows = static_cast<int>(nueral_net_def.output_size);
  int cols = previous_layer + 1;
  Eigen::MatrixX<float> matrix;
  matrix.resize(rows, cols);
  thetas.push_back(std::move(matrix));

  // Now do Random initialization
  RandomizeThetas(&thetas);
  return thetas;
}


}  // namespace ml

#endif  // THETA_CREATOR_H_
