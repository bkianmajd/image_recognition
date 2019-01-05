#ifndef TEMPLATE_RECOGNITION_SIMPLE_SIMPLE_RECOGNITION_H_
#define TEMPLATE_RECOGNITION_SIMPLE_SIMPLE_RECOGNITION_H_

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "external_libraries/googletest/include/gtest/gtest_prod.h"
#include "libraries/image_recognition/template_recognition/template_recognition_interface.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace template_recognition {

class SimpleRecognition : public TemplateRecognitionInterface {
 public:
  SimpleRecognition() = default;
  ~SimpleRecognition() {}

  bool RegisterImage(const std::string& abs_path_image_name) override;

  bool RegisterTemplate(TemplateId template_id,
                        const std::string& abs_path_image_name) override;

  bool RegisterTemplate(TemplateId template_id, const std::vector<char>& bytes) override;

  // Gets the point for a specific image id.
  std::vector<Point> GetTemplateMatch(TemplateId template_id) override;

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

}  // namespace template_recognition

#endif  // TEMPLATE_RECOGNITION_SIMPLE_SIMPLE_RECOGNITION_H_
