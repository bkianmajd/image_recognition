#ifndef IMAGE_COMPARER_H_
#define IMAGE_COMPARER_H_

#include "helpers/directory_finder.h"
#include "libraries/image_def/image_def.h"

#include <memory>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

namespace image {

/// Compares the incoming image to jpg images in a directory
class Comparer {
 public:
  Comparer();

  /// Returns the first relative string of the image
  std::string FindImageInDirectory(const Image& image);

  /// Loads all jpg image in a directory
  bool LoadCache(helpers::DirectoryFinder directory_finder);

  /// Gets the directory finder for the loaded cache
  helpers::DirectoryFinder GetDirectoryFinder();

  /// static function to simply Compare two images. The reason this is static is
  /// because no state is needed to run this function.
  bool Compare(const Image& image_one, const Image& image_two);

 private:
  std::unique_ptr<helpers::DirectoryFinder> directory_finder_;
  std::vector<cv::Mat> matricies_;
};

}  // namespace image

#endif  // IMAGE_COMPARER_H_
