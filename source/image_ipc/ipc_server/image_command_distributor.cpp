#include "image_ipc/ipc_server/image_command_distributor.h"

#include "external_libraries/protobuf/src/google/protobuf/any.pb.h"
#include "schema/compiled_files/template_match.pb.h"
#include "schema/compiled_files/test_proto.pb.h"

namespace ipc {
namespace ipc_server {

namespace {}  // namespace

ImageCommandDistributor::ImageCommandDistributor(FileManager* file_manager)
    : file_manager_(file_manager) {}

void ImageCommandDistributor::Distribute(std::string& string) {
  google::protobuf::Any any;
  any.ParseFromString(string);

  if (any.Is<TestProto>()) {
    TestProto test;
    any.UnpackTo(&test);
    std::cout << test.test_bool() << std::endl;
  };

  if (any.Is<StoreImageRequest>()) {
    StoreImageRequest request;
    any.UnpackTo(&request);

    file_manager_->StoreImage(request.image().c_str(), request.size(),
                              request.image_name());
  }
}

}  // namespace ipc
}  // namespace ipc_server
