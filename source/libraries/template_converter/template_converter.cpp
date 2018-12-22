#include "libraries/template_converter/template_converter.h"

#include <cassert>

namespace template_recognition {
namespace {

constexpr int kVectorSize = 3;
constexpr double kProbabilityThreshold[3] = {.92, .95, .90};
constexpr int kVicinityThreshold = 50;

}  // namespace

TemplateConverter::TemplateConverter() {}

image_recognition::Point TemplateConverter::Convert(
    const std::vector<template_recognition::Point>& points) {
  image_recognition::Point return_point;
  return_point.valid = false;

  // Check the vector size
  if (points.size() != kVectorSize) {
    std::cerr << "points not == 3" << std::endl;
    return return_point;
  }

  int max_index = GetLargestProbabilityIndex(points);

  // Check the vicinity - return if success
  if (CheckVicinity(points[0], points[1]) &&
      CheckVicinity(points[1], points[2])) {
    return ConvertToPoint(points[max_index]);
  }

  // Check the probability limits - return if success
  // The third probability is unreliable so ignore it
  for (int i = 0; i < 2; ++i) {
    if (points[i].probability > kProbabilityThreshold[i]) {
      return ConvertToPoint(points[i]);
    }
  }

  // return if false
  return return_point;
}

image_recognition::Point TemplateConverter::ConvertToPoint(
    const template_recognition::Point& point) {
  image_recognition::Point return_point;
  return_point.valid = true;
  return_point.x = point.x;
  return_point.y = point.y;
  return return_point;
}

int TemplateConverter::GetLargestProbabilityIndex(
    const std::vector<template_recognition::Point>& points) {
  int max_probability_index = 0;
  for (int i = 0; i < kVectorSize; ++i) {
    const template_recognition::Point& point = points[i];
    if (point.probability > max_probability_index) {
      max_probability_index = point.probability;
      max_probability_index = i;
    }
  }
  return max_probability_index;
}

// Returns true if vicinity is consistent
bool TemplateConverter::CheckVicinity(
    const template_recognition::Point& point_1,
    const template_recognition::Point& point_2) {
  return (point_1.x < point_2.x + kVicinityThreshold) &&
         (point_1.x > point_2.x - kVicinityThreshold) &&
         (point_1.y < point_2.y + kVicinityThreshold) &&
         (point_1.y > point_2.y - kVicinityThreshold);
}

}  // namespace template_recognition
