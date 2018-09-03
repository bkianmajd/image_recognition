#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

namespace ipc {

class FileManager {
 public:
  FileManager() = default;

  bool StoreFile(const char* data, size_t size,
                 const std::string& abs_directory_file);

  bool DeleteFile(const std::string& abs_directory_file);

  std::vector<char> ReadFile(const std::string& abs_directory_file);
};

}  // namespace ipc

#endif  // FILE_MANAGER_H_
