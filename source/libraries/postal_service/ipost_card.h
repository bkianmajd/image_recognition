#ifndef POSTAL_SERVICE_IPOST_CARD_H_
#define POSTAL_SERVICE_IPOST_CARD_H_

#include "external_libraries/protobuf-3.5.x/src/google/protobuf/any.pb.h"

namespace postal_service {

/// @interface IPostcard
///  All post cards map to a corresponding protobuf.
class IPostCard {
 public:
  virtual ~IPostCard() {}

  /// TODO() the return should be the base class of protobuf
  virtual google::protobuf::Any CreateProtobuf() = 0;
};

}  // namespace postal_service

#endif  // POSTAL_SERVICE_IPOST_CARD_H_
