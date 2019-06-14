#ifndef PROTOBUF_LOADER_H_
#define PROTOBUF_LOADER_H_

#include <chrono>
#include <string>

#include <google/protobuf/message.h>

#include "helpers/directory_finder.h"
#include "helpers/file_manager.h"

namespace proto {

/// This class stores protobuf binaries and loads them
class ProtobufLoader {
 public:
  ProtobufLoader(const std::string& abs_path);

  bool StoreProtobuf(const google::protobuf::Message& message);

  bool LoadProtobuf(google::protobuf::Message* message);

 private:
  const std::string abs_path_;
};

}  // namespace proto
#endif  // PROTOBUF_LOADER_H_
