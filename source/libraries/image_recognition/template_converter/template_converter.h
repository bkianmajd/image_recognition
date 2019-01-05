#ifndef TEMPLATE_CONVERTER_H_
#define TEMPLATE_CONVERTER_H_

#include <vector>

#include "libraries/image_recognition/image_recognition_defs.h"
#include "libraries/image_recognition/template_recognition/template_recognition_defs.h"

namespace template_recognition {

// Responsible for converting a template_recognition::Points to
// image_recognition::Point
class TemplateConverter {
 public:
  TemplateConverter();

  /// Converts a vector to a point by finding the best match
  image_recognition::Point Convert(
      const std::vector<template_recognition::Point>& points);

 private:
  int GetLargestProbabilityIndex(
      const std::vector<template_recognition::Point>& points);

  bool CheckVicinity(const template_recognition::Point& point_1,
                     const template_recognition::Point& point_2);

  image_recognition::Point ConvertToPoint(
      const template_recognition::Point& point);
};

}  // namespace template_recognition

#endif  // TEMPLATE_CONVERTER_H_
