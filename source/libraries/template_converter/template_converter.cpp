#include "libraries/template_converter/template_converter.h"

namespace template_recognition {
namespace {

constexpr double kProbabilityThreshold = .95;

}  // namespace

TemplateConverter::TemplateConverter() {}

image_recognition::Point TemplateConverter::Convert(
    const std::vector<template_recognition::Point>& points) {
  double max_probability = 0;
  image_recognition::Point return_point;
  return_point.valid = false;

  for (const template_recognition::Point& point : points) {
    if (point.probability > max_probability) {
      max_probability = point.probability;
      return_point.x = point.x;
      return_point.y = point.y;
    }
  }

  if (max_probability > kProbabilityThreshold) {
    return_point.valid = true;
  }

  return return_point;
}

}  // namespace template_recognition
