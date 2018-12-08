#include "libraries/template_converter/template_converter.h"

#include <cassert>

namespace template_recognition {
namespace {

constexpr double kProbabilityThreshold[3] = {.92, .95, .50};
constexpr int kVicinityThreshold = 50;

// Returns true if vicinity is consistent
bool CheckVicinity(const template_recognition::Point& point_1,
                   const template_recognition::Point& point_2) {
  return (point_1.x < point_2.x + kVicinityThreshold) &&
         (point_1.x > point_2.x - kVicinityThreshold) &&
         (point_1.y < point_2.y + kVicinityThreshold) &&
         (point_1.y > point_2.y - kVicinityThreshold);
}

}  // namespace

TemplateConverter::TemplateConverter() {}

image_recognition::Point TemplateConverter::Convert(
    const std::vector<template_recognition::Point>& points) {
  image_recognition::Point return_point;

  if (points.size() != 3) {
    std::cerr << "points not == 3" << std::endl;
    return return_point;
  }

  double max_probability = 0;
  int max_probability_index = 0;
  return_point.valid = true;

  for (int i = 0; i < 3; ++i) {
    const template_recognition::Point& point = points[i];
    if (point.probability > max_probability) {
      max_probability = point.probability;
      max_probability_index = i;
    }

    if (point.probability < kProbabilityThreshold[i]) {
      return_point.valid = false;
    }
  }

  // vicinity threshold
  return_point.valid =
      return_point.valid && CheckVicinity(points[0], points[1]);
  return_point.valid =
      return_point.valid && CheckVicinity(points[0], points[2]);

  return_point.x = points[max_probability_index].x;
  return_point.y = points[max_probability_index].y;
  return return_point;
}

}  // namespace template_recognition
