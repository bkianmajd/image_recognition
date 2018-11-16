#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

namespace helpers {

class FileManager {
 public:
  FileManager() = default;

  static bool StoreFile(const char* data, size_t size,
                 const std::string& abs_directory_file);

  static bool DeleteFile(const std::string& abs_directory_file);

  static std::vector<char> ReadFile(const std::string& abs_directory_file);
};

}  // namespace helpers

#endif  // FILE_MANAGER_H_
