#include "image_ipc/ipc_server/image_command_distributor.h"

#include "external_libraries/protobuf/src/google/protobuf/any.pb.h"
#include "helpers/memory_helper.hpp"
#include "schema/compiled_files/test_proto.pb.h"

namespace ipc {
namespace ipc_server {

namespace {}  // namespace

ImageCommandDistributor::ImageCommandDistributor(
    FileManager* file_manager, ResponseHandler* response_handler)
    : file_manager_(file_manager), response_handler_(response_handler) {}

void ImageCommandDistributor::Distribute(const google::protobuf::Any& any) {
  if (any.Is<TestProto>()) {
    TestProto test;
    any.UnpackTo(&test);
    std::cout << test.test_bool() << std::endl;

    response_handler_->Push(std::make_unique<TestProto>());
    return;
  };

  if (any.Is<StoreImageRequest>()) {
    StoreImageRequest request;
    any.UnpackTo(&request);
    std::unique_ptr<StoreImageResponse> response =
        std::make_unique<StoreImageResponse>();
    Handle(request, response.get());
    response_handler_->Push(std::move(response));
    return;
  }

  std::cout << "IMAGE_COMMAND_DISTRIBUTOR:string unrecogegnized" << std::endl;
}

void ImageCommandDistributor::Handle(const StoreImageRequest& request,
                                     StoreImageResponse* response) {
  bool result = file_manager_->StoreFile(request.image().c_str(),
                                         request.size(), request.image_name());
  response->set_success(result);
}

}  // namespace ipc
}  // namespace ipc_server
