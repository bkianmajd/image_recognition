#ifndef IMAGE_UPLOADER_H_
#define IMAGE_UPLOADER_H_

#include <QString>
#include <QStringList>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest_prod.h"
#include "helpers/directory_finder.h"
#include "libraries/image_def/image_def.h"
#include "libraries/image_file_manager/image_file_manager_interface.h"

namespace image {

// Upload template images to the session directory when given a directory
// through the constructor
class ImageUploader {
 public:
  explicit ImageUploader(
      const helpers::DirectoryFinder& directory_of_templates);

  void SearchAndStoreImages();

  void RemoveAllImages();

  const std::vector<std::string>& StoredImages() const;

  const Image& GetImage(const std::string& image_name) const;

  std::vector<std::string> SearchImages() const;

 private:
  FRIEND_TEST(ImageUploaderTest, GetImageListTest);

  bool Store(const QString& file_name);

  QStringList GetImageList() const;

  const helpers::DirectoryFinder directory_of_templates_;

  std::vector<std::string> stored_images_;
  std::unordered_map<std::string, Image> image_map_;

  Image error_image_;
};

}  // namespace image

#endif  // IMAGE_UPLOADER_H_
