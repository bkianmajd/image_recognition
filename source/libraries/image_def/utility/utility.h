#ifndef PIPELINE_UTILITY_H_
#define PIPELINE_UTILITY_H_

#include <vector>

#include "libraries/image_def/image_def.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace image {
constexpr size_t kBlueIndex = 0;
constexpr size_t kGreenIndex = 1;
constexpr size_t kRedIndex = 2;

Image ConvertToRawBytes(const cv::Mat& img);

void Print(const cv::Vec3b& vec);

cv::Mat ConvertImageToMatrix(const Image& image);

}  // namespace image

#endif  // PIPELINE_UTILITY_H_
