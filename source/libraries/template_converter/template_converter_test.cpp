#include "libraries/template_converter/template_converter.h"

#include <iostream>

#include "gtest/gtest.h"

namespace template_recognition {
namespace {

template_recognition::Point CreatePoint(double probability, int x, int y) {
  template_recognition::Point point;
  point.probability = probability;
  point.x = x;
  point.y = y;
  return point;
}

std::vector<template_recognition::Point> TestPoint1() {
  std::vector<template_recognition::Point> points;
  points.push_back(CreatePoint(.966, 75, 451));
  points.push_back(CreatePoint(.983717, 75, 451));
  points.push_back(CreatePoint(.888942, 4, 453));
  return points;
}

}  // namespace

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

TEST_F(TemplateConverterTest, ConvertSuccessTest) {
  std::vector<template_recognition::Point> points = TestPoint1();
  image_recognition::Point point = template_converter_.Convert(points);
  EXPECT_TRUE(point.valid);
  EXPECT_EQ(point.x, 75);
  EXPECT_EQ(point.y, 451);
}

}  // namespace template_recognition
