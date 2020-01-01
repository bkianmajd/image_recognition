#include "libraries/nueral_net/common/data_point_solver.h"

#include <iostream>

#include <fstream>
#include "gtest/gtest.h"
#include "helpers/directory_finder.h"

namespace ml {
namespace {

constexpr char input_layer_str[] = "input_layer.txt";
constexpr char output_layer_str[] = "output_layer.txt";
constexpr char theta1_str[] = "theta1.txt";
constexpr char theta2_str[] = "theta2.txt";

constexpr float kNear = .0001f;
constexpr float kExpectedCost = .0345f;
constexpr float kExpectedGradient1 = -1.0990f;
constexpr float kExpectedGradient2 = 0.3163f;

const std::string path_from_workspace = "libraries/nueral_net/common/test_data";

std::vector<float> ReadVectorFromFile(const std::string& str) {
  std::vector<float> values;
  std::ifstream file(str.c_str());

  if (!file.is_open()) {
    return values;
  }

  while (file.good()) {
    float x = 0;
    file >> x;
    if (file.eof()) {
      break;
    }
    values.push_back(x);
  }

  file.close();
  return values;
}

Eigen::MatrixX<float> ReadMatrixFromFile(const std::string& str) {
  Eigen::MatrixX<float> result;

  // Open the file
  std::ifstream file(str.c_str());
  if (!file.is_open()) {
    return result;
  }
  if (file.eof()) {
    return result;
  }

  // The first two values are rows and columns
  int rows = 0;
  file >> rows;
  int cols = 0;
  file >> cols;

  // Resize the matrix
  result.resize(rows, cols);

  // Extract the float values from the file
  std::vector<float> values;
  while (!file.eof()) {
    float x = 0;
    file >> x;
    values.push_back(x);
  }

  // put the values into the matrix
  size_t current_index = 0;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      assert(current_index != values.size());
      result(i, j) = values[current_index++];
    }
  }

  file.close();

  return result;
}

}  // namespace

class DataPointSolverTest : public testing::Test {
 public:
  DataPointSolverTest() {
    // Get input layer
    std::vector<float> input_values = ReadVectorFromFile(
        test_directory_.GetAbsPathOfTargetFile(input_layer_str));
    assert(input_values.size() > 0);
    Layer input_layer(input_values);

    // Get output layer
    std::vector<float> output_values = ReadVectorFromFile(
        test_directory_.GetAbsPathOfTargetFile(output_layer_str));
    assert(output_values.size() > 0);
    Layer output_layer(output_values);

    std::vector<Theta> thetas;

    // Get Theta1
    Eigen::MatrixX<float> theta1 =
        ReadMatrixFromFile(test_directory_.GetAbsPathOfTargetFile(theta1_str));
    assert(theta1.rows() > 0 && theta1.cols() > 0);
    thetas.emplace_back(theta1);

    // Get Theta2
    Eigen::MatrixX<float> theta2 =
        ReadMatrixFromFile(test_directory_.GetAbsPathOfTargetFile(theta2_str));
    assert(theta2.rows() > 0 && theta2.cols() > 0);
    thetas.emplace_back(theta2);

    data_point_solver_.reset(
        new DataPointSolver(input_layer, thetas, output_layer));
  }

 protected:
  helpers::DirectoryFinder test_directory_ =
      helpers::CreateDirectoryFinderFromWorkspace(path_from_workspace);

  std::unique_ptr<DataPointSolver> data_point_solver_;
};
TEST_F(DataPointSolverTest, ConstructDestruct) {}

TEST_F(DataPointSolverTest, ForwardPropogateTest) {
  SingleDataPointResult result = data_point_solver_->Solve();
  EXPECT_NEAR(kExpectedCost, result.cost_without_regularization, kNear);

  // Check the check sum of theta 1
  ASSERT_EQ(2, result.gradients_without_regularization.size());
  float total_check_sum = 0;
  for (int i = 0; i < result.gradients_without_regularization[0].rows(); ++i) {
    for (int j = 0; j < result.gradients_without_regularization[0].cols();
         ++j) {
      const ThetaGradient& theta_gradient =
          result.gradients_without_regularization[0];
      total_check_sum += theta_gradient(i, j);
    }
  }
  EXPECT_NEAR(total_check_sum, kExpectedGradient1, kNear);

  // Check the check sum of theta 2
  ASSERT_EQ(2, result.gradients_without_regularization.size());
  total_check_sum = 0;
  for (int i = 0; i < result.gradients_without_regularization[1].rows(); ++i) {
    for (int j = 0; j < result.gradients_without_regularization[1].cols();
         ++j) {
      const ThetaGradient& theta_gradient =
          result.gradients_without_regularization[1];
      total_check_sum += theta_gradient(i, j);
    }
  }
  EXPECT_NEAR(total_check_sum, kExpectedGradient2, kNear);
}

}  // namespace ml
