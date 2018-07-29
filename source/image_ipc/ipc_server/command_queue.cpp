#include "image_ipc/ipc_server/command_queue.h"

namespace ipc {
namespace ipc_server {

void CommandQueue::Push(std::unique_ptr<ICommand> command) {
  command_queue_.push_back(std::move(command));
}

bool CommandQueue::Empty() const { return command_queue_.empty(); }

std::unique_ptr<ICommand> CommandQueue::Pop() {
  if (Empty()) {
    return nullptr;
  }

  std::unique_ptr<ICommand> command = std::move(command_queue_.front());
  command_queue_.pop_back();

  return command;
}

}  // namespace ipc
}  // namespace ipc_server
