#include "libraries/image_uploader/image_uploader.h"

#include <QDirIterator>
#include <iostream>
#include <string>

#include "helpers/file_manager/file_manager.h"

namespace image_recognition {

ImageUploader::ImageUploader(
    ImageFileManagerInterface* file_manager_interface,
    const helpers::DirectoryFinder& directory_of_templates)
    : directory_of_templates_(directory_of_templates),
      image_file_manager_session_(file_manager_interface) {}

void ImageUploader::SearchAndStoreImages() {
  QStringList images = GetImageList();
  foreach (QString file_name, images) { Store(file_name); }
}

void ImageUploader::Store(const QString& file_name) {
  const std::string& abs_path_image =
      directory_of_templates_.GetAbsPathOfTargetFile(file_name.toStdString());

  // Grab the raw data
  std::vector<char> raw_data = helpers::FileManager::ReadFile(abs_path_image);

  if (raw_data.size() == 0) {
    std::cerr << "Raw data size = 0 " << abs_path_image << std::endl;
    return;
  }

  if (!image_file_manager_session_->StoreImage(file_name.toStdString(),
                                               raw_data)) {
    std::cerr << "Failed to store image " << abs_path_image << std::endl;
  }
}

QStringList ImageUploader::GetImageList() {
  const QString path(directory_of_templates_.GetAbsPath().c_str());

  QDir directory(path);
  QStringList images = directory.entryList(QStringList() << "*.jpg"
                                                         << "*.JPG",
                                           QDir::Files);

  return images;
}

}  // namespace image_recognition
