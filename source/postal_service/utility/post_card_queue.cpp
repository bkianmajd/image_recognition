#include "postal_service/utility/post_card_queue.h"
#include "helpers/memory_helper.hpp"

namespace postal_service {

void PostCardQueue::Push(
    std::unique_ptr<::google::protobuf::Message> response_message) {
  // auto unique =
  // std::make_unique<::google::protobuf::Message>(response_message);
  queue_.push(std::move(response_message));
}

bool PostCardQueue::Empty() const { return queue_.empty(); }

google::protobuf::Any PostCardQueue::CreateProtobuf() {
  // Caller is responsible for making sure queue_ is not empty
  assert(!queue_.empty());
  const std::unique_ptr<::google::protobuf::Message>& message = queue_.front();

  google::protobuf::Any any;
  any.PackFrom(*message);
  queue_.pop();
  return any;
}

}  // namespace postal_service
