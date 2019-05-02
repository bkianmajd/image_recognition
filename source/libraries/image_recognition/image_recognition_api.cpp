#include "libraries/image_recognition/image_recognition_api.h"

#include "gtest/gtest_prod.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager.h"
#include "helpers/memory_helper.hpp"
#include "libraries/image_file_manager/image_file_manager.h"
#include "libraries/image_recognition/template_converter/template_converter.h"
#include "libraries/image_recognition/template_recognition/simple/simple_recognition.h"
#include "libraries/image_recognition/template_recognition/template_recognition_defs.h"

namespace recognition {
namespace {

constexpr bool debug = false;
const std::string kBigImageName = "big_image.jpg";

void DebugPoints(const std::string& template_image_name,
                 const std::vector<ProbabilityPoint>& points) {
  std::cout << "------" << template_image_name << "-----" << std::endl;
  for (const ProbabilityPoint& point : points) {
    std::cout << "prob: " << point.probability << " ";
    std::cout << "(" << point.x << "," << point.y << ")" << std::endl;
  }
}

}  // namespace

ImageRecognitionApi::ImageRecognitionApi(
    const helpers::DirectoryFinder& template_directory)
    : template_directory_(template_directory),
      image_uploader_(template_directory_),
      template_recognition_(new SimpleRecognition()) {
  // Sets the images from the template directory equal to the session directory
  // and registers the images with the template recognition
  RegisterTemplates();

  // Unused function
  (void)DebugPoints;
}

ImageRecognitionApi::~ImageRecognitionApi() {
  image_uploader_.RemoveAllImages();
}

bool ImageRecognitionApi::SetBigImage(const std::vector<char>& image_bytes) {
  if (!template_recognition_->RegisterImage(image_bytes)) {
    std::cerr << "failed to register file " << kBigImageName << std::endl;
    return false;
  }

  return true;
}

Point ImageRecognitionApi::TemplateMatch(
    const std::string& template_image_name) {
  Point point;

  std::vector<ProbabilityPoint> t_point =
      template_recognition_->GetTemplateMatch(template_image_name);

  if(debug) {
    DebugPoints(template_image_name, t_point);
  }

  TemplateConverter template_converter;
  return template_converter.Convert(t_point);
}

void ImageRecognitionApi::RegisterTemplates() {
  image_uploader_.SearchAndStoreImages();
  const std::vector<std::string>& images = image_uploader_.StoredImages();
  for (const std::string& image_name : images) {
    const image::Image& image = image_uploader_.GetImage(image_name);
    if (image.size() == 0) {
      std::cerr << "problem getting image from uploader" << std::endl;
    }
    if (!template_recognition_->RegisterTemplate(image_name, image)) {
      std::cerr << "problem loading image " << image_name << std::endl;
    }
  }
}

bool ImageRecognitionApi::AddTemplateImage(
    const std::vector<char>& image_bytes,
    const std::string& template_image_name) {
  if (!template_recognition_->RegisterTemplate(template_image_name,
                                               image_bytes)) {
    std::cerr << "Template_recognition_->RegisterTemplate failed!" << std::endl;
    return false;
  }

  return true;
}

}  // namespace recognition
