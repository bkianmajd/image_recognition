#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_

#include <QImage>
#include <cstdint>
#include <memory>
#include "helpers/directory_finder.h"

namespace ipc {
namespace ipc_server {

namespace internal {
constexpr QImage::Format kFormat = QImage::Format::Format_RGB32;
}  // namespace internal

class FileManager {
 public:
  FileManager(const std::string& directory);

  void StoreImage(const uchar* data, int size, const std::string& file_name,
                  QImage::Format format = internal::kFormat);

 private:
  const std::string directory_;
};

}  // namespace ipc_server
}  // namespace ipc

#endif  // FILE_MANAGER_H_
