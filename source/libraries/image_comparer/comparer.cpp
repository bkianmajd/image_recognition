#include "libraries/image_comparer/comparer.h"

#include <iostream>

#include "helpers/file_manager/file_manager.h"
#include "libraries/image_comparer/compare_algorithm.h"
#include "libraries/image_def/utility/utility.h"
#include "libraries/image_def/utility/utility.h"

namespace image {

Comparer::Comparer(const helpers::DirectoryFinder& directory_finder)
    : directory_finder_(directory_finder), image_uplodaer_(directory_finder) {}

std::string Comparer::FindImageInDirectory(const Image& image) {
  cv::Mat matrix = ConvertImageToMatrix(image);
  std::size_t index;

  // the index corresponds to the image name
  const std::vector<std::string>& image_names = image_uplodaer_.StoredImages();

  for (index = 0; index < matricies_.size(); ++index) {
    // print out image name for debugging
    // std::cout << image_names[index] << std::endl;

    // Found match
    if (CompareWithPercentage(matrix, matricies_[index])) {
      return image_names[index];
    }
    // Didn't find match
  }

  // No match found
  return std::string();
}

bool Comparer::LoadCache() {
  image_uplodaer_.RemoveAllImages();
  image_uplodaer_.SearchAndStoreImages();
  matricies_.clear();

  std::vector<std::string> image_names = image_uplodaer_.StoredImages();
  for (const std::string& image_name : image_names) {
    const Image& image = image_uplodaer_.GetImage(image_name);
    if (image.size() == 0) {
      std::cerr << "image was not loaded properly " << image_name << std::endl;
      continue;
    }
    matricies_.push_back(ConvertImageToMatrix(image));
  }
  return true;
}

/// Gets the directory finder for the loaded cache
helpers::DirectoryFinder Comparer::GetDirectoryFinder() {
  return directory_finder_;
}

}  // namespace image
