#ifndef MAIL_DISTRIBUTOR_QUEUE_H_
#define MAIL_DISTRIBUTOR_QUEUE_H_

#include <queue>
#include "external_libraries/protobuf-3.5.x/src/google/protobuf/any.pb.h"
#include "libraries/postal_service/imail_distributor.h"

namespace postal_service {

/// @class MailDistributorQueue stores the any message into a queue. Simply
/// wraps a queue.
class MailDistributorQueue : public postal_service::IMailDistributor {
 public:
  MailDistributorQueue() = default;
  ~MailDistributorQueue() {}

  virtual void Distribute(const google::protobuf::Any& any) override;

  bool Empty() const;

  int Size() const;

  void Pop();

  const google::protobuf::Any& Front() const;

 private:
  std::queue<google::protobuf::Any> queue_;
};

}  // namespace postal_service

#endif  // MAIL_DISTRIBUTOR_QUEUE_H_
