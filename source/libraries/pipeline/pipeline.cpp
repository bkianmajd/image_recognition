#include "libraries/pipeline/pipeline.h"

#include <iostream>

#include "libraries/pipeline/crop/vertical_crop.h"
#include "libraries/pipeline/filter/noise_reducer.h"
#include "libraries/image_def/utility/utility.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace image {

Pipeline::Pipeline() {}

bool Pipeline::AddToPipeline(PipelineType pipeline_types) {
  types_.push_back(pipeline_types);
  return true;
}

void Pipeline::ResetPipeline() { types_.clear(); }

std::vector<Image> Pipeline::Run(const Image& image) {
  std::vector<Image> image_vector;

  std::vector<cv::Mat> matrix_vector;
  matrix_vector.push_back(ConvertImageToMatrix(image));

  for (PipelineType type : types_) {
    switch (type) {
      case PipelineType::NOISE_REDUCTION:
        FilterNoiseMatrix(&matrix_vector);
        break;
      case PipelineType::VERTICAL_CROPPING:
        VerticalCrop(&matrix_vector);
        break;
      default:
        std::cerr << "type not handled " << static_cast<int>(type) << std::endl;
    }
  }

  // Convert matrix vector to an image vector
  for (const cv::Mat& mat : matrix_vector) {
    image_vector.push_back(image::ConvertToRawBytes(mat));
  }

  return image_vector;
}

}  // namespace image
