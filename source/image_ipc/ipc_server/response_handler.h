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

  void Push(std::unique_ptr<::google::protobuf::Message> response_message);

  bool Empty() const;

  virtual google::protobuf::Any CreateProtobuf() override;

 private:
  std::queue<std::unique_ptr<::google::protobuf::Message>> queue_;
};

}  // namespace ipc_server
}  // namespace ipc

#endif  // IRESPONSE_H_
