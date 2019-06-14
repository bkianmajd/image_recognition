#ifndef LIBRARIES_CACHE_MANAGER_H_
#define LIBRARIES_CACHE_MANAGER_H_

#include <unordered_map>

#include "external_libraries/libchrome/base/optional.h"
#include "gtest/gtest_prod.h"
#include "helpers/directory_finder.h"
#include "libraries/protobuf_loader/protobuf_loader.h"

#include "schema/compiled_files/test_proto.pb.h"

namespace proto {

/// Automatically loads and stores a protobuf from a directory
template <typename ProtoType>
class CacheManager {
 public:
  CacheManager(const helpers::DirectoryFinder& cached_directory,
               bool read_only = false)
      : initialized_(false),
        proto_loader_(cached_directory.GetAbsPathOfTargetFile(
            proto_type_.descriptor()->name())),
        read_only_(read_only) {}

  ~CacheManager() {
    if (!read_only_) {
      ShutdownStore();
    }
  }

  CacheManager(const CacheManager&) = delete;
  CacheManager& operator=(const CacheManager&) = delete;

  // Resets the binary data file
  void Reset() {
    if (read_only_) {
      return;
    }
    proto_type_.Clear();
    ShutdownStore();
  }

  // some unique int as a key
  // some protobuf message as value
  ProtoType* Get() {
    if (!initialized_) {
      InitializeLoad();
    }
    return &proto_type_;
  }

 private:
  void InitializeLoad() {
    initialized_ = true;
    proto_loader_.LoadProtobuf(&proto_type_);
  }
  void ShutdownStore() {
    initialized_ = false;
    proto_loader_.StoreProtobuf(proto_type_);
  }

  bool initialized_;
  proto::ProtobufLoader proto_loader_;
  ProtoType proto_type_;
  bool read_only_;
};

}  // namespace proto

#endif  // LIBRARIES_CACHE_MANAGER_H_
