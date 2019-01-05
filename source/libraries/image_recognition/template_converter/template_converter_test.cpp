#include "libraries/image_recognition/template_converter/template_converter.h"

#include <iostream>

#include "gtest/gtest.h"

namespace recognition {
namespace {

ProbabilityPoint CreatePoint(double probability, int x, int y) {
  ProbabilityPoint point;
  point.probability = probability;
  point.x = x;
  point.y = y;
  return point;
}

std::vector<ProbabilityPoint> TestPoint1() {
  std::vector<ProbabilityPoint> points;
  points.push_back(CreatePoint(.966, 75, 451));
  points.push_back(CreatePoint(.983717, 75, 451));
  points.push_back(CreatePoint(.888942, 4, 453));
  return points;
}

}  // namespace

class TemplateConverterTest : public testing::Test {
 public:
  TemplateConverterTest() {}
  ~TemplateConverterTest() = default;

 protected:
  TemplateConverter template_converter_;
};
TEST_F(TemplateConverterTest, ConstructDestruct) {}

TEST_F(TemplateConverterTest, ConvertTest) {
  std::vector<ProbabilityPoint> points;
  Point point = template_converter_.Convert(points);
  EXPECT_FALSE(point.valid);
}

TEST_F(TemplateConverterTest, ConvertSuccessTest) {
  std::vector<ProbabilityPoint> points = TestPoint1();
  Point point = template_converter_.Convert(points);
  EXPECT_TRUE(point.valid);
  EXPECT_EQ(point.x, 75);
  EXPECT_EQ(point.y, 451);
}

}  // namespace recognition
