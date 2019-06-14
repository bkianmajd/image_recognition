#include "libraries/protobuf_loader/protobuf_loader.h"

namespace proto {

ProtobufLoader::ProtobufLoader(const std::string& abs_path)
    : abs_path_(abs_path) {}

bool ProtobufLoader::StoreProtobuf(const google::protobuf::Message& message) {
  std::string binary_output;
  message.SerializeToString(&binary_output);

  if (!helpers::FileManager::StoreFile(binary_output.data(),
                                       binary_output.size(), abs_path_)) {
    std::cerr << "Failed to store file" << std::endl;
    return false;
  }
  return true;
}

bool ProtobufLoader::LoadProtobuf(google::protobuf::Message* message) {
  std::vector<char> binary_data = helpers::FileManager::ReadFile(abs_path_);
  if (binary_data.size() == 0) {
    return false;
  }

  message->ParseFromArray(binary_data.data(),
                          static_cast<int>(binary_data.size()));
  return true;
}

}  // namespace proto
