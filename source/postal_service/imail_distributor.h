#ifndef POSTAL_SERVICE_IMAIL_DISTRIBUTOR_H_
#define POSTAL_SERVICE_IMAIL_DISTRIBUTOR_H_

#include <string>
#include "external_libraries/protobuf/src/google/protobuf/any.pb.h"

namespace postal_service {

/// Class converts byte array to postcards. The concrete class decides what to
/// do with the postcard.
class IMailDistributor {
 public:
  virtual ~IMailDistributor() {}

  virtual void Distribute(const google::protobuf::Any& any) = 0;
};

}  // mail_distributor

#endif  // POSTAL_SERVICE_IMAIL_DISTRIBUTOR_H_
