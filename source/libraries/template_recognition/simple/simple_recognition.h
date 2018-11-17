#ifndef TEMPLATE_RECOGNITION_SIMPLE_SIMPLE_RECOGNITION_H_
#define TEMPLATE_RECOGNITION_SIMPLE_SIMPLE_RECOGNITION_H_

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "external_libraries/googletest/include/gtest/gtest_prod.h"
<<<<<<< HEAD
#include "libraries/template_recognition/template_recognition_interface.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
=======
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "libraries/template_recognition/template_recognition_interface.h"
>>>>>>> 43d87c17b85c57b9e757c93177e9cbb162a3df2e

namespace template_recognition {

class SimpleRecognition : public TemplateRecognitionInterface {
 public:
  SimpleRecognition() = default;
<<<<<<< HEAD
  ~SimpleRecognition() {}
=======
>>>>>>> 43d87c17b85c57b9e757c93177e9cbb162a3df2e

  bool RegisterImage(const std::string& abs_path_image_name) override;

  bool RegisterTemplate(TemplateId template_id,
                        const std::string& abs_path_image_name) override;

  // Gets the point for a specific image id.
<<<<<<< HEAD
  std::vector<Point> GetTemplateMatch(TemplateId template_id) override;
=======
  Point GetTemplateMatch(TemplateId template_id) override;
>>>>>>> 43d87c17b85c57b9e757c93177e9cbb162a3df2e

  std::string GetFilePath() const;

 private:
  FRIEND_TEST(SimpleRecognitionTest, TemplateStorageTest);

  bool CheckImage(const std::string& abs_path_image_name);

  // The big image to compare the template images against.
  cv::Mat big_image_;

  // unordered map containing the templates
  std::unordered_map<TemplateId, cv::Mat> template_map_;
};

}  // namespace template_recognition

#endif  // TEMPLATE_RECOGNITION_SIMPLE_SIMPLE_RECOGNITION_H_
