#include "libraries/protobuf_loader/protobuf_loader.h"

namespace proto {

ProtobufLoader::ProtobufLoader(const helpers::DirectoryFinder& directory,
                               const std::string& target_file)
    : directory_(directory), target_file_(target_file) {}

bool ProtobufLoader::StoreProtobuf(const google::protobuf::Message& message) {
  std::string binary_output;
  message.SerializeToString(&binary_output);

  if (!helpers::FileManager::StoreFile(
          binary_output.data(), binary_output.size(),
          directory_.GetAbsPathOfTargetFile(target_file_))) {
    std::cerr << "Failed to store file" << std::endl;
    return false;
  }
  return true;
}

bool ProtobufLoader::LoadProtobuf(google::protobuf::Message* message) {
  std::vector<char> binary_data = helpers::FileManager::ReadFile(
      directory_.GetAbsPathOfTargetFile(target_file_));
  if (binary_data.size() == 0) {
    std::cerr << "Failed to read file" << std::endl;
    return false;
  }

  message->ParseFromArray(binary_data.data(),
                          static_cast<int>(binary_data.size()));
  return true;
}

}  // namespace proto
