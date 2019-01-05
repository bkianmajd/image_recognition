#include "libraries/image_uploader/image_uploader.h"

#include <QDirIterator>
#include <iostream>
#include <string>

#include "helpers/file_manager/file_manager.h"

namespace image {

ImageUploader::ImageUploader(
    const helpers::DirectoryFinder& directory_of_templates)
    : directory_of_templates_(directory_of_templates) {}

void ImageUploader::SearchAndStoreImages() {
  QStringList images = GetImageList();
  foreach (QString file_name, images) {
    if (Store(file_name)) {
      stored_images_.push_back(file_name.toStdString());
    }
  }
}

bool ImageUploader::Store(const QString& file_name) {
  const std::string& abs_path_image =
      directory_of_templates_.GetAbsPathOfTargetFile(file_name.toStdString());

  // Grab the raw data
  std::vector<char> raw_data = helpers::FileManager::ReadFile(abs_path_image);

  if (raw_data.size() == 0) {
    std::cerr << "Raw data size = 0 " << abs_path_image << std::endl;
    return false;
  }

  Image& image = raw_data;
  image_map_[file_name.toStdString()] = image;

  return true;
}

QStringList ImageUploader::GetImageList() const {
  const QString path(directory_of_templates_.GetAbsPath().c_str());

  QDir directory(path);
  QStringList images = directory.entryList(QStringList() << "*.jpg"
                                                         << "*.JPG",
                                           QDir::Files);

  return images;
}

const std::vector<std::string>& ImageUploader::StoredImages() const {
  return stored_images_;
}

void ImageUploader::RemoveAllImages() {
  stored_images_.clear();
  image_map_.clear();
}

const Image& ImageUploader::GetImage(const std::string& image_name) const {
  auto it = image_map_.find(image_name);
  if (it == image_map_.end()) {
    std::cerr << "asking for incorrect image " << image_name.c_str()
              << std::endl;
    return error_image_;
  }

  return it->second;
}

std::vector<std::string> ImageUploader::SearchImages() const {
  std::vector<std::string> images;
  QStringList list = GetImageList();
  foreach (QString file_name, list) {
    images.push_back(file_name.toStdString());
  }
  return images;
}

}  // namespace image
