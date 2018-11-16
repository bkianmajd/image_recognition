#include "libraries/template_converter/template_converter.h"

#include <iostream>

#include "gtest/gtest.h"

namespace template_recognition {

class TemplateConverterTest : public testing::Test {
 public:
  TemplateConverterTest() {}

 protected:
  TemplateConverter template_converter_;
};
TEST_F(TemplateConverterTest, ConstructDestruct) {}

TEST_F(TemplateConverterTest, ConvertTest) {
  std::vector<template_recognition::Point> points;
  image_recognition::Point point = template_converter_.Convert(points);
  EXPECT_FALSE(point.valid);
}

}  // namespace template_recognition
