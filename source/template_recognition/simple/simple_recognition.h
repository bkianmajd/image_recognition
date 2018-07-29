#ifndef TEMPLATE_RECOGNITION_SIMPLE_SIMPLE_RECOGNITION_H_
#define TEMPLATE_RECOGNITION_SIMPLE_SIMPLE_RECOGNITION_H_

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "external_libraries/googletest/include/gtest/gtest_prod.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "template_recognition/template_recognition_interface.h"

namespace template_recognition {

class SimpleRecognition : public TemplateRecognitionInterface {
 public:
  SimpleRecognition(std::string file_path);

  bool RegisterImage(const std::string& image_name) override;

  bool RegisterTemplate(TemplateId template_id,
                        const std::string& image_name) override;

  // Gets the point for a specific image id.
  Point GetTemplateMatch(TemplateId template_id) override;

  std::string GetFilePath() const;

 private:
  FRIEND_TEST(RecognitionTest, TemplateStorageTest);

  bool CheckImage(const std::string& file_name_with_path);

  // The location of the files, ideally a data folder
  std::string data_file_path_;

  // The big image to compare the template images against.
  cv::Mat big_image_;

  // unordered map containing the templates
  std::unordered_map<TemplateId, cv::Mat> template_map_;
};

}  // namespace template_recognition

#endif  // TEMPLATE_RECOGNITION_SIMPLE_SIMPLE_RECOGNITION_H_
