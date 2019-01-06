#ifndef COMPARE_ALGORITHM_H_
#define COMPARE_ALGORITHM_H_

#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace image {

bool Compare(const cv::Mat& mat_one, const cv::Mat& mat_two);

}  // namespace image

#endif  // COMPARE_ALGORITHM_H_
