#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

namespace ipc {

class FileManager {
 public:
  FileManager(const std::string& directory);

  bool StoreFile(const char* data, size_t size, const std::string& file_name);

  bool DeleteFile(const std::string& file_name);

  std::vector<char> ReadFile(const std::string& file_name);

 private:
  const std::string directory_;
};

}  // namespace ipc

#endif  // FILE_MANAGER_H_
