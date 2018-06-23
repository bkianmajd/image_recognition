#ifndef MAIL_DISTRIBUTOR_SIMPLE_H_
#define MAIL_DISTRIBUTOR_SIMPLE_H_

#include "postal_service/mail_distributor_simple/imail_distributor.h"

namespace postal_service {

class MailDistributorSimple : public IMailDistributor {
 public:
  MailDistributorSimple() {}

  void Distribute(std::string& string);

 private:
};

}  // namespace mail_distributor_simple

#endif  // MAIL_DISTRIBUTOR_SIMPLE_H_
