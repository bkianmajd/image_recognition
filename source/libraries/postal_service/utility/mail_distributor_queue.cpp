#include "libraries/postal_service/utility/mail_distributor_queue.h"
#include "helpers/memory_helper.hpp"

namespace postal_service {

bool MailDistributorQueue::Empty() const { return queue_.empty(); }

void MailDistributorQueue::Distribute(const google::protobuf::Any& any) {
  queue_.push(any);
}

int MailDistributorQueue::Size() const { return queue_.size(); }

const google::protobuf::Any& MailDistributorQueue::Front() const {
  return queue_.front();
}

void MailDistributorQueue::Pop() { queue_.pop(); }

}  // namespace postal_service
