#ifndef COMMAND_QUEUE_H_
#define COMMAND_QUEUE_H_

#include <memory>
#include <vector>

#include "image_ipc/ipc_server/icommand.h"
#include "postal_service/imail_distributor.h"

namespace ipc {
namespace ipc_server {

class CommandQueue final {
 public:
  CommandQueue() {}

  void Push(std::unique_ptr<ICommand>);

  bool Empty() const;

  std::unique_ptr<ICommand> Pop();

 private:
  std::vector<std::unique_ptr<ICommand>> command_queue_;
};

}  // namespace ipc
}  // namespace ipc_server

#endif  // COMMAND_QUEUE_H_
