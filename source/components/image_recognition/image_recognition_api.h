#ifndef IMAGE_RECOGNITION_API_
#define IMAGE_RECOGNITION_API_

#include <memory>
#include <unordered_map>

#include "components/image_recognition/image_recognition_defs.h"
#include "helpers/directory_finder.h"
#include "libraries/image_file_manager/image_file_manager_interface.h"
#include "libraries/image_uploader/image_uploader.h"
#include "libraries/template_recognition/template_recognition_interface.h"

namespace image_recognition {

/// Class that acts as the API to easily recognize images and templates. A
/// template directory is passed into this class. The
/// directory of jpg images are automatically loaded into the sesion directory.
class ImageRecognitionApi {
 public:
  explicit ImageRecognitionApi(
      const helpers::DirectoryFinder& template_directory,
      const helpers::DirectoryFinder& session_directory);

  ~ImageRecognitionApi();

  bool SetBigImage(const std::vector<char>& image_bytes);

  Point TemplateMatch(const std::string& template_image_name);

  /// Adds the template image name to the session directory. If the template
  /// image already exists, will remove the image.
  bool AddTemplateImage(const std::vector<char>& image_bytes,
                        const std::string& template_image_name);

 private:
  void RegisterTemplates();
  bool RegisterTemplate(const std::string& template_image_name);

  // The directory of all the template images
  helpers::DirectoryFinder template_directory_;

  // Creates a session directory - for now a static fixed folder
  helpers::DirectoryFinder session_directory_;
  std::unique_ptr<ImageFileManagerInterface> session_file_manager_;

  // Uploads all the images into the session directory
  ImageUploader image_uploader_;

  // Template recognition
  std::unique_ptr<template_recognition::TemplateRecognitionInterface>
      template_recognition_;

  int last_id_ = 0;
  std::unordered_map<std::string, int> template_id_map_;
};

}  // namespace image_recognition

#endif  // IMAGE_RECOGNITION_API_
