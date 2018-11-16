#ifndef IMAGE_UPLOADER_H_
#define IMAGE_UPLOADER_H_

#include <QString>
#include <QStringList>

#include "gtest/gtest_prod.h"
#include "helpers/directory_finder.h"
#include "libraries/image_file_manager/image_file_manager_interface.h"

namespace image_recognition {

// Upload template images to the session directory when given a directory
// through the constructor
class ImageUploader {
 public:
  ImageUploader(ImageFileManagerInterface* file_manager_interface,
                const helpers::DirectoryFinder& directory_of_templates);

  void SearchAndStoreImages();

 private:
  FRIEND_TEST(ImageUploaderTest, GetImageListTest);

  void Store(const QString& file_name);

  QStringList GetImageList();

  const helpers::DirectoryFinder directory_of_templates_;
  ImageFileManagerInterface* image_file_manager_session_;
};

}  // namespace image_uploader

#endif  // IMAGE_UPLOADER_H_
