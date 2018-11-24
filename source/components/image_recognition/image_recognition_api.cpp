#include "components/image_recognition/image_recognition_api.h"

#include "gtest/gtest_prod.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager/file_manager.h"
#include "helpers/memory_helper.hpp"
#include "libraries/image_file_manager/image_file_manager.h"
#include "libraries/template_converter/template_converter.h"
#include "libraries/template_recognition/simple/simple_recognition.h"
#include "libraries/template_recognition/template_recognition_defs.h"

namespace image_recognition {
namespace {

const std::string kBigImageName = "big_image.jpg";

void DebugPoints(const std::string& template_image_name,
                 const std::vector<template_recognition::Point>& points) {
  std::cout << "------" << template_image_name << "-----" << std::endl;
  for (const template_recognition::Point& point : points) {
    std::cout << "prob: " << point.probability << " ";
    std::cout << "(" << point.x << "," << point.y << ")" << std::endl;
  }
}

}  // namespace

ImageRecognitionApi::ImageRecognitionApi(
    const helpers::DirectoryFinder& template_directory,
    const helpers::DirectoryFinder& session_directory)
    : template_directory_(template_directory),
      session_directory_(session_directory),
      session_file_manager_(
          std::make_unique<ImageFileManager>(session_directory_)),
      image_uploader_(session_file_manager_.get(), template_directory_),
      template_recognition_(new template_recognition::SimpleRecognition()) {
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
  std::string abs_file =
      session_directory_.GetAbsPathOfTargetFile(kBigImageName);
  // remove the big image before storing the new image
  helpers::FileManager::DeleteFile(abs_file);

  if (!helpers::FileManager::StoreFile(image_bytes.data(), image_bytes.size(),
                                       abs_file)) {
    std::cerr << "failed to store file " << abs_file << std::endl;
    return false;
  }

  if (!template_recognition_->RegisterImage(abs_file)) {
    std::cerr << "failed to register file " << kBigImageName << std::endl;
    return false;
  }

  return true;
}

Point ImageRecognitionApi::TemplateMatch(
    const std::string& template_image_name) {
  Point point;
  auto it = template_id_map_.find(template_image_name);
  if (it == template_id_map_.end()) {
    point.valid = false;
    return point;
  }

  std::vector<template_recognition::Point> t_point =
      template_recognition_->GetTemplateMatch(it->second);

  DebugPoints(template_image_name, t_point);

  template_recognition::TemplateConverter template_converter;
  return template_converter.Convert(t_point);
}

void ImageRecognitionApi::RegisterTemplates() {
  image_uploader_.SearchAndStoreImages();
  const std::vector<std::string>& images = image_uploader_.StoredImages();
  for (const std::string& image : images) {
    RegisterTemplate(image);
  }
}

bool ImageRecognitionApi::AddTemplateImage(
    const std::vector<char>& image_bytes,
    const std::__cxx11::string& template_image_name) {
  std::string abs_file =
      session_directory_.GetAbsPathOfTargetFile(template_image_name);
  // remove the big image before storing the new image
  helpers::FileManager::DeleteFile(abs_file);

  // Convert image_bytes into a file into the sesion directory
  if (!helpers::FileManager::StoreFile(image_bytes.data(), image_bytes.size(),
                                       abs_file)) {
    std::cerr << "failed to store file " << abs_file << std::endl;
    return false;
  }
  return RegisterTemplate(template_image_name);
}

bool ImageRecognitionApi::RegisterTemplate(
    const std::string& template_image_name) {
  std::string abs_file =
      session_directory_.GetAbsPathOfTargetFile(template_image_name);

  // Check if the template id already exists with the image name
  auto it = template_id_map_.find(template_image_name);
  if (it == template_id_map_.end()) {
    if (!template_recognition_->RegisterTemplate(last_id_, abs_file)) {
      std::cerr << "Template_recognition_->RegisterTemplate failed!"
                << std::endl;
      return false;
    }

    // Create a new template id
    template_id_map_[template_image_name] = last_id_++;
    return true;
  }

  // Use the old template id
  if (!template_recognition_->RegisterTemplate(it->second, abs_file)) {
    std::cerr << "Template_recognition_->RegisterTemplate failed!" << std::endl;
    return false;
  }

  return true;
}

}  // namespace image_recognition
