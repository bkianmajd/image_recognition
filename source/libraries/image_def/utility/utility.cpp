#include "libraries/image_def/utility/utility.h"

#include <iostream>

// https://docs.opencv.org/2.4/doc/user_guide/ug_mat.html
// https://docs.opencv.org/3.0-beta/modules/imgcodecs/doc/reading_and_writing_images.html
namespace image {

void Print(const cv::Vec3b& vec) {
  std::cout << static_cast<int>(vec.val[0]) << " ";
  std::cout << static_cast<int>(vec.val[1]) << " ";
  std::cout << static_cast<int>(vec.val[2]) << std::endl;
}

std::vector<char> ConvertToRawBytes(const cv::Mat& img) {
  if (img.rows <= 0 || img.cols <= 0) {
    return std::vector<char>();
  }

  std::vector<uchar> output;
  cv::imencode(".jpg", img, output);
  return std::vector<char>(output.begin(), output.end());
}

cv::Mat ConvertImageToMatrix(const Image& image) {
  cv::Mat mat;

  if (image.size() == 0) {
    std::cerr << "image is empty";
    return mat;
  }

  return cv::imdecode(image, cv::IMREAD_COLOR);
}

}  // namespace image
