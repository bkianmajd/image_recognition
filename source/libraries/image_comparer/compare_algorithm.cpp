#include "libraries/image_comparer/compare_algorithm.h"

#include <iostream>

#include "helpers/compare.h"
#include "libraries/image_def/utility/utility.h"

namespace image {
namespace {

constexpr bool debug = false;
constexpr float kThreshold = 50.0;
constexpr double kPassPercentageThreshold = .95;

inline bool CompareIntensity(const cv::Vec3b& intensity_one,
                             const cv::Vec3b& intensity_two) {
  if (debug) {
    std::cout << static_cast<int>(intensity_one[kBlueIndex]) << " "
              << static_cast<int>(intensity_two[kBlueIndex]) << std::endl;
  }
  return helpers::CompareEpsilon(intensity_one[kBlueIndex],
                                 intensity_two[kBlueIndex], kThreshold) &&
         helpers::CompareEpsilon(intensity_one[kGreenIndex],
                                 intensity_two[kGreenIndex], kThreshold) &&
         helpers::CompareEpsilon(intensity_one[kRedIndex],
                                 intensity_two[kRedIndex], kThreshold);
}

}  // namespace

bool Compare(const cv::Mat& mat_one, const cv::Mat& mat_two) {
  if (mat_one.rows != mat_two.rows) {
    return false;
  }
  if (mat_one.cols != mat_two.cols) {
    return false;
  }

  for (int i = 0; i < mat_one.rows; ++i) {
    for (int j = 0; j < mat_one.cols; ++j) {
      const cv::Vec3b& intensity_one = mat_one.at<cv::Vec3b>(cv::Point(j, i));
      const cv::Vec3b& intensity_two = mat_two.at<cv::Vec3b>(cv::Point(j, i));
      if (!CompareIntensity(intensity_one, intensity_two)) {
        return false;
      }
    }
  }

  return true;
}

bool CompareWithPercentage(const cv::Mat& mat_one, const cv::Mat& mat_two) {
  if (mat_one.rows != mat_two.rows) {
    return false;
  }
  if (mat_one.cols != mat_two.cols) {
    return false;
  }

  int total = 0;
  double fail_counter = 0;
  for (int i = 0; i < mat_one.rows; ++i) {
    for (int j = 0; j < mat_one.cols; ++j) {
      total++;
      const cv::Vec3b& intensity_one = mat_one.at<cv::Vec3b>(cv::Point(j, i));
      const cv::Vec3b& intensity_two = mat_two.at<cv::Vec3b>(cv::Point(j, i));
      if (!CompareIntensity(intensity_one, intensity_two)) {
        fail_counter++;
      }
    }
  }

  double fail_percentage = fail_counter / static_cast<double>(total);
  // std::cout << "fail percentage " << fail_percentage << std::endl;
  return (1.0 - fail_percentage) > kPassPercentageThreshold;
}

}  // namespace image
