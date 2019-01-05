#ifndef NOISE_REDUCER_H_
#define NOISE_REDUCER_H_

#include <vector>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace image {

void FilterNoiseMatrix(cv::Mat* img);

void FilterNoiseMatrix(std::vector<cv::Mat>* img_vector);

}  // namespace image

#endif  // NOISE_REDUCER_H_
