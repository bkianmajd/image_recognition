#include "libraries/image_recognition/template_recognition/simple/simple_recognition.h"

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "external_libraries/googletest/include/gtest/gtest_prod.h"
#include "libraries/image_def/utility/utility.h"
#include "libraries/image_recognition/template_recognition/template_recognition_interface.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace recognition {
namespace {

constexpr int kMaxTemplateMatchTypes = 6;
}

bool SimpleRecognition::RegisterImage(const image::Image& image) {
  if (image.size() == 0) {
    return false;
  }

  // Image exists. Register it with OpenCv.
  big_image_ = image::ConvertImageToMatrix(image);
  return true;
}

bool SimpleRecognition::RegisterTemplate(TemplateId template_id,
                                         const image::Image& bytes) {
  // Check if template_id is used, remove it
  auto it = template_map_.find(template_id);
  if (it != template_map_.end()) {
    template_map_.erase(it);
  }

  // Add a new template id
  template_map_.insert(std::pair<TemplateId, cv::Mat>(
      template_id, cv::imdecode(bytes, cv::IMREAD_COLOR)));

  // check to see if the mat is empty
  it = template_map_.find(template_id);
  if (it->second.empty()) {
    template_map_.erase(it);
    return false;
  }

  return true;
}

// Gets the point for a specific image id.
std::vector<ProbabilityPoint> SimpleRecognition::GetTemplateMatch(
    TemplateId template_id) {
  std::vector<ProbabilityPoint> return_point_vector;

  // Check if tempate id is in the template_map
  auto it = template_map_.find(template_id);
  if (it == template_map_.end()) {
    std::cerr << "could not find template id " << template_id << std::endl;
    return return_point_vector;
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

  for (int template_match_method = 0;
       template_match_method < kMaxTemplateMatchTypes;
       ++template_match_method) {
    // Skip the non-norm elements
    if (template_match_method == CV_TM_SQDIFF ||
        template_match_method == CV_TM_CCORR ||
        template_match_method == CV_TM_CCOEFF) {
      continue;
    }

    // Do the matching
    cv::matchTemplate(big_image_, it->second, result, template_match_method);

    // avoiding normalizing result here to read the probabilities
    // cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

    // Localizing the best match with minMaxLoc
    double minVal;
    double maxVal;
    cv::Point minLoc, maxLoc;
    cv::Point matchLoc;

    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

    // For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all
    // the other methods, the higher the better
    if (template_match_method == CV_TM_SQDIFF ||
        template_match_method == CV_TM_SQDIFF_NORMED) {
      matchLoc = minLoc;
    } else {
      matchLoc = maxLoc;
    }

    ProbabilityPoint return_point;
    return_point.isValid = true;
    // Update the probabilities
    switch (template_match_method) {
      case CV_TM_SQDIFF:
        return_point.probability = minVal;
        break;
      case CV_TM_SQDIFF_NORMED:
        return_point.probability = 1 - minVal;
        break;
      case CV_TM_CCORR:
        return_point.probability = maxVal;
        break;
      case CV_TM_CCORR_NORMED:
        return_point.probability = maxVal;
        break;
      case CV_TM_CCOEFF:
        return_point.probability = maxVal;
        break;
      case CV_TM_CCOEFF_NORMED:
        return_point.probability = maxVal;
        break;
      default:
        return_point.isValid = false;
    }

    // store matchLoc into the return point
    return_point.x = matchLoc.x;
    return_point.y = matchLoc.y;
    return_point.template_match_type = template_match_method;
    return_point_vector.push_back(std::move(return_point));
  }
  return return_point_vector;
}

}  // namespace recognition
