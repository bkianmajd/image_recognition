#include "image_ipc/file_manager/file_manager.h"

#include <iostream>
#include <string>

namespace ipc {
namespace ipc_server {

FileManager::FileManager(const std::string& directory)
    : directory_(directory) {}

void FileManager::StoreImage(const uchar* data, int size,
                             const std::string& file_name,
                             QImage::Format format) {
  // const char format_char = (char)format;
  // QImage qimage = QImage::fromData(data, size, &format_char);

  // Create the image file
  std::string directory_file_path = directory_;
  directory_file_path.append(file_name);
  helpers::DirectoryFinder directory_finder(directory_file_path.c_str());

  std::cout << directory_finder.GetAbsPathRelativeToWorkspace() << std::endl;
  // qimage.save(directory_file_path, format);
}

}  // namespace ipc_server
}  // namespace ipc
