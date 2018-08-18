#ifndef IRESPONSE_H_
#define IRESPONSE_H_

#include <queue>
#include "external_libraries/protobuf/src/google/protobuf/any.pb.h"
#include "postal_service/ipost_card.h"

namespace ipc {
namespace ipc_server {

/// @class Repsonse handler sends an IPostCard in the queue
class ResponseHandler : public postal_service::IPostCard {
 public:
  ~ResponseHandler() {}

  void Push(::google::protobuf::Message&& response_message) {
    queue_.push(response_message);
  }

  void Empty() const { return queue_.empty(); }

  virtual google::protobuf::Any CreateProtobuf() override {
    // caller is responsible for making sure queue_ is not empty
    assert(!queue_.empty());
    const ::google::protobuf::Message& message = queue_.front();

    // Does an unnecessary copy...revisit this later. Might be better to return
    // a string from the post card. Any should only be used as a proto
    // definition. The base class takes care of any.
    google::protobuf::Any any;
    any.PackFrom(message);
    queue_.pop();
    return any;
  }

 private:
  std::queue<::google::protobuf::Message> queue_;
};

}  // namespace ipc_server
}  // namespace ipc

#endif  // IRESPONSE_H_
