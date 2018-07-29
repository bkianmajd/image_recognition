#ifndef IRESPONSE_H_
#define IRESPONSE_H_

#include "external_libraries/protobuf/src/google/protobuf/any.pb.h"
#include "postal_service/ipost_card.h"

namespace ipc {

// class IResponse is a simple wrapper around IPostCard
class IResponse : public postal_service::IPostCard {
 public:
  virtual ~IResponse() {}

  virtual google::protobuf::Any CreateProtobuf() = 0;
};

}  // namespace ipc

#endif  // IRESPONSE_H_
