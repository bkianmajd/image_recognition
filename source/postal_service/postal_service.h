#ifndef POSTAL_SERVICE_POSTAL_SERVICE_H_
#define POSTAL_SERVICE_POSTAL_SERVICE_H_

#include <memory>

#include "gtest/gtest_prod.h"
#include "postal_service/com_layer/icarrier.h"
#include "postal_service/imail_distributor.h"
#include "postal_service/ipost_card.h"

namespace postal_service {

enum Type {
  server = 0,
  client,
};

/// @interface IPostcard
///  All post cards map to a corresponding protobuf.
class PostalService {
 public:
  explicit PostalService(Type type = Type::client);

  // This is a blocking call
  void Init(const com_layer::ConnectionInfo& connection_info);

  void SendPostCard(IPostCard& post_card) const;

  void GetMail(IMailDistributor& mail_distributor);

  bool IsOpen() const;

 private:
  std::unique_ptr<com_layer::ICarrier> carrier_;

  std::string received_byte_array_;
};

}  // namespace postal_service

#endif  // POSTAL_SERVICE_POSTAL_SERVICE_H_
