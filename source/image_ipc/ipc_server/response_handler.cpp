#include "image_ipc/ipc_server/response_handler.h"

#include "helpers/memory_helper.hpp"

namespace ipc {
namespace ipc_server {

void ResponseHandler::Push(
    std::unique_ptr<::google::protobuf::Message> response_message) {
  // auto unique =
  // std::make_unique<::google::protobuf::Message>(response_message);
  queue_.push(std::move(response_message));
}

bool ResponseHandler::Empty() const { return queue_.empty(); }

google::protobuf::Any ResponseHandler::CreateProtobuf() {
  // caller is responsible for making sure queue_ is not empty
  assert(!queue_.empty());
  const std::unique_ptr<::google::protobuf::Message>& message = queue_.front();

  google::protobuf::Any any;
  any.PackFrom(*message);
  queue_.pop();
  return any;
}

}  // namespace ipc_server
}  // namespace ipc
