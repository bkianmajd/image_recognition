#ifndef TEMPLATE_CONVERTER_H_
#define TEMPLATE_CONVERTER_H_

#include <vector>

#include "components/image_recognition/image_recognition_defs.h"
#include "libraries/template_recognition/template_recognition_defs.h"

namespace template_recognition {

class TemplateConverter {
 public:
  TemplateConverter();

  /// Converts a vector to a point by finding the best match
  image_recognition::Point Convert(
      const std::vector<template_recognition::Point>& points);

 private:
};

}  // namespace template_recognition

#endif  // TEMPLATE_CONVERTER_H_
