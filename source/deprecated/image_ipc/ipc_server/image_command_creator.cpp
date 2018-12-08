#include "image_ipc/ipc_server/image_command_creator.h"

#include "external_libraries/protobuf/src/google/protobuf/any.pb.h"
#include "helpers/memory_helper.hpp"
#include "schema/compiled_files/test_proto.pb.h"

namespace ipc {
namespace ipc_server {
namespace {}  // namespace

ImageCommandCreator::ImageCommandCreator(
    ImageCommandDispatcher* dispatcher,
    postal_service::PostCardQueue* response_handler)
    : dispatcher_(dispatcher), response_handler_(response_handler) {}

void ImageCommandCreator::Distribute(const google::protobuf::Any& any) {
  if (any.Is<TestProto>()) {
    TestProto test;
    any.UnpackTo(&test);
    std::cout << test.test_bool() << std::endl;

    response_handler_->Push(std::make_unique<TestProto>());
    return;
  };

  if (any.Is<ipc_interface::StoreImageRequest>()) {
    ipc_interface::StoreImageRequest request;
    any.UnpackTo(&request);
    std::unique_ptr<ipc_interface::StoreImageResponse> response =
        std::make_unique<ipc_interface::StoreImageResponse>();
    dispatcher_->Handle(request, response.get());
    response_handler_->Push(std::move(response));
    return;
  }

  std::cout << "IMAGE_COMMAND_Creator:string unrecogegnized" << std::endl;
}

}  // namespace ipc
}  // namespace ipc_server
