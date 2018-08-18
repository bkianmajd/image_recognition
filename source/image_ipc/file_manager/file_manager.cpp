#include "image_ipc/file_manager/file_manager.h"

#include <QDebug>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include "helpers/directory_finder.h"

namespace ipc {
namespace ipc_server {

FileManager::FileManager(const std::string& directory)
    : directory_(directory) {}

bool FileManager::StoreFile(const char* data, size_t size,
                            const std::string& file_name) {
  // Open the image file
  std::string directory_file_path = directory_;
  directory_file_path.append(file_name);

  // Open the destination file
  FILE* fp = std::fopen(directory_file_path.c_str(), "wb");
  if (!fp) {
    return false;
  }

  // Write the entire buffer to file
  std::size_t sz_wrote = std::fwrite(data, sizeof(char), size, fp);
  std::fclose(fp);

  return sz_wrote == size;
}

bool FileManager::DeleteFile(const std::string& file_name) {
  std::string directory_file_path = directory_;
  directory_file_path.append(file_name);

  // a zero value is returned on success
  return std::remove(directory_file_path.c_str()) == 0;
}

std::vector<char> FileManager::ReadFile(const std::string& file_name) {
  std::string file_path = directory_;
  file_path.append(file_name);

  // Open the source file
  FILE* fp = std::fopen(file_path.c_str(), "rb");
  if (!fp) {
    return std::vector<char>();
  };

  // Get its length (in bytes)
  if (std::fseek(fp, 0, SEEK_END) != 0)  // This should typically succeed
  {                                      // (beware the 2Gb limitation, though)
    std::fclose(fp);
    return std::vector<char>();
  }

  size_t file_sz = std::ftell(fp);
  if (file_sz == 0) {
    std::fclose(fp);
    return std::vector<char>();
  }

  // reset fp
  std::rewind(fp);

  // store the binary data
  std::vector<char> binary_data(file_sz);
  // Read the entire file into the buffer
  std::size_t size_wrote = std::fread(binary_data.data(), sizeof binary_data[0],
                                      binary_data.size(), fp);
  if (size_wrote != file_sz) {
    std::fclose(fp);
    return std::vector<char>();
  }

  std::fclose(fp);
  return binary_data;
}

}  // namespace ipc_server
}  // namespace ipc