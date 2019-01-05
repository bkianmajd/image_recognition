#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <memory>
#include <vector>

#include "libraries/image_def/image_def.h"

namespace image {

enum class PipelineType {
  UNKNOWN = 0,
  // Reduces the noise
  NOISE_REDUCTION,
  // Converts the lowest pixel frequency to black, everything else white
  LIMIT_BLACK,
  // Crops the top and bottom of an image
  HORIZONTAL_CROPPING,
  // Splits images into several images
  VERTICAL_CROPPING,
};

class Pipeline {
 public:
  Pipeline();

  bool AddToPipeline(PipelineType pipeline_types);
  void ResetPipeline();

  std::vector<Image> Run(const Image& image);

 private:
  Pipeline UpdateNextPipeline();

  std::vector<PipelineType> types_;
};

}  // namespace image

#endif  // PIPELINE_H_
