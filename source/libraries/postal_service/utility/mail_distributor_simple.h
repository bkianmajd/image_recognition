#ifndef MAIL_DISTRIBUTOR_SIMPLE_H_
#define MAIL_DISTRIBUTOR_SIMPLE_H_

#include "libraries/postal_service/imail_distributor.h"

namespace postal_service {

class MailDistributorSimple : public IMailDistributor {
 public:
  MailDistributorSimple() {}

  void Distribute(const google::protobuf::Any& any);

 private:
};

}  // namespace mail_distributor_simple

#endif  // MAIL_DISTRIBUTOR_SIMPLE_H_
