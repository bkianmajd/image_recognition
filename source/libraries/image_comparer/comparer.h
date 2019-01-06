#ifndef IMAGE_COMPARER_H_
#define IMAGE_COMPARER_H_

#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "helpers/directory_finder.h"
#include "libraries/image_def/image_def.h"
#include "libraries/image_uploader/image_uploader.h"

namespace image {

/// Compares the incoming image to jpg images in a directory
class Comparer {
 public:
  explicit Comparer(const helpers::DirectoryFinder& directory_finder);

  /// Returns the first relative string of the image
  std::string FindImageInDirectory(const Image& image);

  /// Loads all jpg image in a directory
  bool LoadCache();

  /// Gets the directory finder for the loaded cache
  helpers::DirectoryFinder GetDirectoryFinder();

 private:
  helpers::DirectoryFinder directory_finder_;
  ImageUploader image_uplodaer_;
  std::vector<cv::Mat> matricies_;
};

}  // namespace image

#endif  // IMAGE_COMPARER_H_
