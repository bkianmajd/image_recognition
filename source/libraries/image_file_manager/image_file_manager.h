#ifndef IMAGE_FILE_MANAGER_H_
#define IMAGE_FILE_MANAGER_H_

#include <string>
#include <unordered_map>

#include "gtest/gtest_prod.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager/file_manager.h"
#include "libraries/image_file_manager/image_file_manager_interface.h"

namespace image_recognition {

/// Class that stores images into a folder for image recognition
class ImageFileManager : public ImageFileManagerInterface {
 public:
  ImageFileManager(const helpers::DirectoryFinder& session_directory);

  bool RemoveImage(const std::string& image_name) override;

  bool StoreImage(const std::string& image_name,
                  const std::vector<char>& image_bytes) override;

 private:
  // The data directory is where all the images are currently stored
  const helpers::DirectoryFinder session_directory_;

  // The map key is the filename, the map value is the stored templateId
  std::unordered_map<std::string, int> stored_template_id_;
};

}  // namespace image_recognition

#endif  // IMAGE_FILE_MANAGER_H_
