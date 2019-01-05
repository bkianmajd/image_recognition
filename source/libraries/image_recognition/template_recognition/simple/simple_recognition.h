#ifndef TEMPLATE_RECOGNITION_SIMPLE_SIMPLE_RECOGNITION_H_
#define TEMPLATE_RECOGNITION_SIMPLE_SIMPLE_RECOGNITION_H_

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "external_libraries/googletest/include/gtest/gtest_prod.h"
#include "libraries/image_def/image_def.h"
#include "libraries/image_recognition/template_recognition/template_recognition_interface.h"

namespace recognition {

class SimpleRecognition : public TemplateRecognitionInterface {
 public:
  SimpleRecognition() = default;
  ~SimpleRecognition() override = default;

  bool RegisterImage(const image::Image& image) override;

  bool RegisterTemplate(TemplateId template_id,
                        const image::Image& image) override;

  // Gets the point for a specific image id.
  std::vector<ProbabilityPoint> GetTemplateMatch(TemplateId template_id) override;

  std::string GetFilePath() const;

 private:
  FRIEND_TEST(SimpleRecognitionTest, TemplateStorageTest);
  FRIEND_TEST(SimpleRecognitionTest, TemplateStorageTest2);

  bool CheckImage(const std::string& abs_path_image_name);

  // The big image to compare the template images against.
  cv::Mat big_image_;

  // unordered map containing the templates
  std::unordered_map<TemplateId, cv::Mat> template_map_;
};

}  // namespace recognition

#endif  // TEMPLATE_RECOGNITION_SIMPLE_SIMPLE_RECOGNITION_H_
