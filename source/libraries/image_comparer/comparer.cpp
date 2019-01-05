#include "libraries/image_comparer/comparer.h"

#include "libraries/image_def/utility/utility.h"

namespace image {

Comparer::Comparer() {}

// Static
bool Comparer::Compare(const Image& image_one, const Image& image_two) {
  (void)image_one;
  (void)image_two;
  return false;
}

/// Returns the first relative string of the image
std::string Comparer::FindImageInDirectory(const Image& image) {
  (void)image;
  return std::string();
}

/// Loads all jpg image in a directory
bool Comparer::LoadCache(helpers::DirectoryFinder directory_finder) {
  directory_finder_.reset(new helpers::DirectoryFinder(directory_finder));

  return true;
}

/// Gets the directory finder for the loaded cache
helpers::DirectoryFinder Comparer::GetDirectoryFinder() {
  return *directory_finder_;
}

}  // namespace image
