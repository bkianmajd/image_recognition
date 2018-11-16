#include "libraries/template_recognition/simple/simple_recognition.h"

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "external_libraries/googletest/include/gtest/gtest_prod.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "libraries/template_recognition/template_recognition_interface.h"

namespace template_recognition {

bool SimpleRecognition::RegisterImage(const std::string& image_with_path) {
  // Find the image in the data file
  if (!CheckImage(image_with_path)) {
    return false;
  }

  // Image exists. Register it with OpenCv.
  big_image_ = cv::imread(image_with_path, 1);
  return true;
}

bool SimpleRecognition::RegisterTemplate(TemplateId template_id,
                                         const std::string& image_with_path) {
  // Find the image in the data file
  if (!CheckImage(image_with_path)) {
    return false;
  }

  // Image exists. Add it to map

  // Check if template_id is used
  auto it = template_map_.find(template_id);
  if (it != template_map_.end()) {
    return false;
  }

  // Add a new template id
  template_map_.insert(std::pair<TemplateId, cv::Mat>(
      template_id, cv::imread(image_with_path, 1)));

  return true;
}

// Gets the point for a specific image id.
Point SimpleRecognition::GetTemplateMatch(TemplateId template_id) {
  const int kMatchMethod = 5;
  Point return_point;

  // Check if tempate id is in the template_map
  auto it = template_map_.find(template_id);
  if (it == template_map_.end()) {
    return_point.isValid = false;
    return return_point;
  }

  // Template image to compare against |big_image_|
  cv::Mat templ;
  it->second.copyTo(templ);

  // Create the result matrix
  int result_cols = big_image_.cols - templ.cols + 1;
  int result_rows = big_image_.rows - templ.rows + 1;

  // Create the result image
  cv::Mat result;
  result.create(result_rows, result_cols, CV_32FC1);

  // Do the matching
  cv::matchTemplate(big_image_, it->second, result, kMatchMethod);
  cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

  // Localizing the best match with minMaxLoc
  double minVal;
  double maxVal;
  cv::Point minLoc, maxLoc;
  cv::Point matchLoc;

  cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

  // For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all
  // the other methods, the higher the better
  if (kMatchMethod == CV_TM_SQDIFF || kMatchMethod == CV_TM_SQDIFF_NORMED) {
    matchLoc = minLoc;
  } else {
    matchLoc = maxLoc;
  }

  // store matchLoc into return point
  return_point.x = matchLoc.x;
  return_point.y = matchLoc.y;
  return return_point;
}

bool SimpleRecognition::CheckImage(const std::string& file_name_with_path) {
  std::ifstream test_open;
  test_open.open(file_name_with_path);
  bool is_open = test_open.is_open();
  test_open.close();
  return is_open;
}

}  // namespace template_recognition
