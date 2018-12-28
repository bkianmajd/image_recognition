#ifndef POSTAL_SERVICE_POSTAL_SERVICE_H_
#define POSTAL_SERVICE_POSTAL_SERVICE_H_

#include <memory>

#include "gtest/gtest_prod.h"
#include "libraries/postal_service/com_layer/carrier_base.h"
#include "libraries/postal_service/imail_distributor.h"
#include "libraries/postal_service/ipost_card.h"

namespace postal_service {

enum class Type {
  server = 0,
  client,
};

/// @interface IPostcard
///  All post cards map to a corresponding protobuf.
class PostalService {
 public:
  explicit PostalService(Type type = Type::client);

  void AsyncInit(const com_layer::ConnectionInfo& connection_info);

  // This is a blocking call and should be called after exec() is running
  bool WaitForOpen();

  void SendMail(const google::protobuf::Message& message) const;

  void GetMail(IMailDistributor& mail_distributor);

  bool IsOpen() const;

 private:
  std::unique_ptr<com_layer::CarrierBase> carrier_;

  std::string received_byte_array_;
};

}  // namespace postal_service

#endif  // POSTAL_SERVICE_POSTAL_SERVICE_H_
