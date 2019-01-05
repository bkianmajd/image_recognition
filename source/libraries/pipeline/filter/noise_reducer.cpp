#include "libraries/pipeline/filter/noise_reducer.h"

#include <iostream>

#include "libraries/image_def/utility/utility.h"

// https://docs.opencv.org/2.4/doc/user_guide/ug_mat.html
// https://docs.opencv.org/3.0-beta/modules/imgcodecs/doc/reading_and_writing_images.html

namespace image {
namespace {
constexpr int kThreshold = 100;

void FlattenColors(cv::Vec3b* vec) {
  if (vec->val[kBlueIndex] + vec->val[kGreenIndex] + vec->val[kRedIndex] >
      kThreshold * 3) {
    vec->val[kBlueIndex] = 255;
    vec->val[kGreenIndex] = 255;
    vec->val[kRedIndex] = 255;
    return;
  }
  vec->val[kBlueIndex] = 0;
  vec->val[kGreenIndex] = 0;
  vec->val[kRedIndex] = 0;
}

}  // namespace

void FilterNoiseMatrix(cv::Mat* img) {
  for (int i = 0; i < img->cols; ++i) {
    for (int j = 0; j < img->rows; ++j) {
      cv::Vec3b& intensity = img->at<cv::Vec3b>(cv::Point(i, j));
      // Print(intensity);
      FlattenColors(&intensity);
    }
  }
}

void FilterNoiseMatrix(std::vector<cv::Mat>* img_vector) {
  for (cv::Mat& mat : *img_vector) {
    FilterNoiseMatrix(&mat);
  }
}

}  // namespace image
