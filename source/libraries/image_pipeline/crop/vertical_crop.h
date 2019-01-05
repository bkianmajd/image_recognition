#ifndef PIPELINE_VERTICAL_CROP_H_
#define PIPELINE_VERTICAL_CROP_H_

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

namespace image {

// Takes a single image and splits it into several images defined on some edge
// detected limits
std::vector<cv::Mat> VerticalCrop(const cv::Mat& img);

// Takes several images and splits it into several more images defined on some
// edge detected limits
void VerticalCrop(std::vector<cv::Mat>* img_vector);

}  // namespace image

#endif  // PIPELINE_VERTICAL_CROP_H_
