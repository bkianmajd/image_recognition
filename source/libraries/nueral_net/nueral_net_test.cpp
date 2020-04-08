#include "libraries/nueral_net/nueral_net.h"

#include <fstream>
#include <iostream>

#include "gtest/gtest.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager.h"

namespace ml {

const std::string kTestDirectory = "libraries/nueral_net/test_files/";
const std::string kInput = "input.txt";
const std::string kOutput = "output.txt";
const std::string kTheta1 = "theta1.txt";
const std::string kTheta2 = "theta2.txt";

// Clasifiers always have to start with zero and be contigious
enum Clasifier {
  One,
  Two,
  Three,
  Four,
  Five,
  Size,
  Seven,
  Eight,
  Nine,
  Zero,
};

NueralNetDef CreateNueralNetDef() {
  NueralNetDef nueral_net_def;
  nueral_net_def.input_size = 400;
  nueral_net_def.output_size = 10;
  nueral_net_def.hidden_layers = {25};
  return nueral_net_def;
};

class DataSetReader {
 public:
  DataSetReader()
      : directory_(
            helpers::CreateDirectoryFinderFromWorkspace(kTestDirectory)) {
    input_stream_.open(directory_.GetAbsPathOfTargetFile(kInput));
    output_stream_.open(directory_.GetAbsPathOfTargetFile(kOutput));
  }

  ~DataSetReader() {
    if (input_stream_.is_open()) {
      input_stream_.close();
    }
    if (output_stream_.is_open()) {
      output_stream_.close();
    }
  }

  bool IsDataAvailable() { return input_stream_.good(); }

  std::pair<InputLayer, Clasifier> GetNextData() {
    InputLayer input_layer;

    // The next 400 data points are your input for 1 test data
    for (int i = 0; i < 400; ++i) {
      float value;
      input_stream_ >> value;
      input_layer.push_back(value);
    }

    // Get the output, and clasify it (convert int to enum)
    int output;
    output_stream_ >> output;
    if (output == 10) {
      return {input_layer, Clasifier::Zero};
    }
    // A one , needs to be registered as an (int) 0, which is an (enum) one.
    // Its this way because matlab has a one as
    // [1 0 0 0 0 0 0...] and matlab has a 10 as
    // [0 0 0 0 0 0 ... 0 1]
    return {input_layer, static_cast<Clasifier>(output-1)};
  }

  Theta GetTestTheta(int index) {
    if (index == 1) {
      return Theta(
          ReadMatrixFromFile(directory_.GetAbsPathOfTargetFile(kTheta1)));
    }
    return Theta(
        ReadMatrixFromFile(directory_.GetAbsPathOfTargetFile(kTheta2)));
  }

 private:
  Eigen::MatrixX<float> ReadMatrixFromFile(const std::string& str) const {
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

  helpers::DirectoryFinder directory_;
  std::ifstream input_stream_;
  std::ifstream output_stream_;

  InputLayer input_layer_;
  Clasifier clasifier_;
};

// Tests the coursera course machine learning example 4
class NueralNetTest : public testing::Test {
 public:
  NueralNetTest() : nueral_net_trainer_(CreateNueralNetDef()) {}

 protected:
  NueralNetTrainer<Clasifier> nueral_net_trainer_;
};
TEST_F(NueralNetTest, ConstructDestruct) {}

// Tests the DataSetReader class correctly imports the input and output txt
// files
TEST_F(NueralNetTest, TestDataSetReader) {
  DataSetReader data_set_reader;
  int count = 0;
  while (data_set_reader.IsDataAvailable()) {
    count++;
    data_set_reader.GetNextData();
  }
  EXPECT_EQ(5000, count);
}

TEST_F(NueralNetTest, TestNueralNet) {
  int count = 0;
  DataSetReader data_set_reader;
  while (data_set_reader.IsDataAvailable()) {
    std::pair<InputLayer, Clasifier> data_set = data_set_reader.GetNextData();
    nueral_net_trainer_.AddDataSet(data_set.first, data_set.second);
    count++;
  }
  ASSERT_EQ(5000, count);

  // Inject theta
  nueral_net_trainer_.thetas_.at(0) = data_set_reader.GetTestTheta(1);
  nueral_net_trainer_.thetas_.at(1) = data_set_reader.GetTestTheta(2);

  nueral_net_trainer_.Train();
  nueral_net_trainer_.Train();
  nueral_net_trainer_.Train();
  nueral_net_trainer_.Train();
  nueral_net_trainer_.Train();
}

}  // namespace ml
