#ifndef IMAGE_RECOGNITION_API_
#define IMAGE_RECOGNITION_API_

#include <memory>
#include <unordered_map>

#include "helpers/directory_finder.h"
#include "libraries/image_file_manager/image_file_manager_interface.h"
#include "libraries/image_recognition/image_recognition_defs.h"
#include "libraries/image_recognition/template_recognition/template_recognition_interface.h"
#include "libraries/image_uploader/image_uploader.h"

namespace recognition {

/// Class that acts as the API to easily recognize images and templates. A
/// template directory is passed into this class. The
/// directory of jpg images are automatically loaded into the sesion directory.
class ImageRecognitionApi {
 public:
  explicit ImageRecognitionApi(const helpers::DirectoryFinder& template_directory);

  ~ImageRecognitionApi();

  bool SetBigImage(const std::vector<char>& image_bytes);

  Point TemplateMatch(const std::string& template_image_name);

  /// Adds the template image name to the session directory. If the template
  /// image already exists, will remove the image.
  bool AddTemplateImage(const std::vector<char>& image_bytes,
                        const std::string& template_image_name);

 private:
  void RegisterTemplates();

  // The directory of all the template images
  helpers::DirectoryFinder template_directory_;

  // Searches all the images into the session directory
  image::ImageUploader image_uploader_;

  // Template recognition
  std::unique_ptr<TemplateRecognitionInterface> template_recognition_;
};

}  // namespace recognition

#endif  // IMAGE_RECOGNITION_API_
