#ifndef NUERAL_NET_DEFS_H_
#define NUERAL_NET_DEFS_H_

#include <cmath>
#include <vector>

namespace ml {

struct NueralNetDef {
  size_t input_size;
  size_t output_size;
  std::vector<int> hidden_layers;
};

struct NueralNetResult {
  NueralNetDef nueralNetDef;
  float regularized_cost;
};



}  // namespace ml

#endif  // NUERAL_NET_DEFS_H_
