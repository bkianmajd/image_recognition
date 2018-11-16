#ifndef IMAGE_RECOGNITION_API_
#define IMAGE_RECOGNITION_API_

#include "components/image_recognition/image_recognition_defs.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager/file_manager.h"

namespace image_recognition {

/// Class that acts as the API to easily recognize images and templates. A
/// template directory is passed into this class. The
/// directory of jpg images are automatically loaded into the sesion directory.
class ImageRecognitionApi {
 public:
  ImageRecognitionApi(helpers::DirectoryFinder template_directory);

  ~ImageRecognitionApi() = default;

  bool SetBigImage(const std::vector<char>& image_bytes);

  Point TemplateMatch(const std::string& template_image_name);

private:
  helpers::DirectoryFinder template_directory_;
};

}  // namespace image_recognition

#endif  // IMAGE_RECOGNITION_API_
