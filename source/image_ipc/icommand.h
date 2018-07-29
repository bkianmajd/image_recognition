#ifndef I_COMMAND_H_
#define I_COMMAND_H_

#include "image_ipc/iresponse.h"
#include "postal_service/imail_distributor.h"

namespace ipc {

class ICommand {
 public:
  virtual ~ICommand() {}

  virtual std::unique_ptr<IResponse> ApplyCommand() = 0;
};

}  // namespace ipc

#endif  // I_COMMAND_H_
