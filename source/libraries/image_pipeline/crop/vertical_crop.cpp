#include "libraries/image_pipeline/crop/vertical_crop.h"

#include "libraries/image_def/utility/utility.h"

#include <algorithm>

namespace image {
namespace {
constexpr int kLightThreshold = 120 * 3;
constexpr int kEnd = -1;

using Range = std::pair<int, int>;

bool IsColumnAllLight(int col, const cv::Mat& mat) {
  for (int j = 0; j < mat.rows; ++j) {
    const cv::Vec3b& intensity = mat.at<cv::Vec3b>(cv::Point(col, j));
    if (intensity[kBlueIndex] + intensity[kGreenIndex] + intensity[kRedIndex] <
        kLightThreshold) {
      return false;
    }
  }
  return true;
}

// Finds the vertical edge of an image using a hard coded threshold.
int FindDarkIndexCol(int start_col_index, const cv::Mat& mat) {
  for (int i = start_col_index; i < mat.cols; ++i) {
    if (!IsColumnAllLight(i, mat)) {
      // There is some darkness in this column, return this index
      return i;
    }
  }
  return kEnd;
}

// Finds the next colomn that is all white.
int FindAllLightCol(int start_col_index, const cv::Mat& mat) {
  for (int i = start_col_index; i < mat.cols; ++i) {
    if (IsColumnAllLight(i, mat)) {
      return i;
    }
  }
  return kEnd;
}

cv::Mat ConvertRangeToMatrix(const Range& range, const cv::Mat& mat) {
  if (range.first == kEnd) {
    return cv::Mat();
  }

  if (range.second == kEnd) {
    return mat.colRange(range.first, mat.cols);
  }

  return mat.colRange(range.first, range.second);
}

}  // namespace

std::vector<cv::Mat> VerticalCrop(const cv::Mat& img) {
  std::vector<cv::Mat> return_vector;

  std::vector<Range> ranges;

  int start_index = 0;
  int end_index = 0;
  // Find the start of the dark image
  while (start_index < img.cols && end_index < img.cols) {
    start_index = FindDarkIndexCol(start_index, img);
    if (start_index == kEnd) {
      break;
    }

    end_index = FindAllLightCol(start_index + 1, img);

    ranges.push_back(std::make_pair(start_index, end_index));
    if (end_index == kEnd) {
      break;
    }
    start_index = end_index + 1;
  }

  // Each range represents an area of the matrix
  for (const Range& range : ranges) {
    return_vector.push_back(ConvertRangeToMatrix(range, img));
  }

  return return_vector;
}

void VerticalCrop(std::vector<cv::Mat>* img_vector) {
  std::vector<cv::Mat> return_vector;

  for (const cv::Mat& mat : *img_vector) {
    std::vector<cv::Mat> cropped_matricies = VerticalCrop(mat);
    for (cv::Mat& cropped_mat : cropped_matricies) {
      return_vector.push_back(std::move(cropped_mat));
    }
  }

  std::swap(return_vector, *img_vector);
}

}  // namespace image
