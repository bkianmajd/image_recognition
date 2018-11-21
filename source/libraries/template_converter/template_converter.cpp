#include "libraries/template_converter/template_converter.h"

namespace template_recognition {
namespace {

constexpr double kProbabilityThreshold = .986;

}  // namespace

TemplateConverter::TemplateConverter() {}

image_recognition::Point TemplateConverter::Convert(
    const std::vector<template_recognition::Point>& points) {
  double sum = 0;
  int count = 0;
  image_recognition::Point return_point;
  return_point.valid = false;

  for (const template_recognition::Point& point : points) {
    sum += point.probability;
    count++;
    return_point.x = point.x;
    return_point.y = point.y;
  }

  double average = sum/count;
  // std::cout << "average " << average << std::endl;

  if (average > kProbabilityThreshold) {
    return_point.valid = true;
  }

  return return_point;
}

}  // namespace template_recognition
