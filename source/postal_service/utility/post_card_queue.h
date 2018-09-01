#ifndef POSTCARDQUEUE_H_
#define POSTCARDQUEUE_H_

#include <queue>
#include <memory>
#include "external_libraries/protobuf/src/google/protobuf/any.pb.h"
#include "postal_service/ipost_card.h"

namespace postal_service {

/// @class PostCardQueue converts protobuf into a postcard
class PostCardQueue : public postal_service::IPostCard {
 public:
  ~PostCardQueue() {}

  void Push(std::unique_ptr<::google::protobuf::Message> response_message);

  bool Empty() const;

  virtual google::protobuf::Any CreateProtobuf() override;

 private:
  std::queue<std::unique_ptr<::google::protobuf::Message>> queue_;
};

}  // namespace postal_service

#endif  // POSTCARDQUEUE_H_
