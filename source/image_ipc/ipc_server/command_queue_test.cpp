#include "image_ipc/ipc_server/command_queue.h"

#include "gtest/gtest.h"
#include "image_ipc/commands/test_command.h"

namespace ipc {
namespace ipc_server {

class CommandQueueTest : public testing::Test {
 public:
  CommandQueueTest() {}

 protected:
  CommandQueue command_queue_;
};

TEST_F(CommandQueueTest, ConstructDestruct) {}

TEST_F(CommandQueueTest, PushTest) {
  command_queue_.Push(std::unique_ptr<ICommand>(new TestCommand));
  EXPECT_FALSE(command_queue_.Empty());
}

TEST_F(CommandQueueTest, PopTest) {
  command_queue_.Push(std::unique_ptr<ICommand>(new TestCommand));

  std::unique_ptr<ICommand> test_command = command_queue_.Pop();
  EXPECT_TRUE(command_queue_.Empty());

  std::unique_ptr<IResponse> response = test_command->ApplyCommand();
  EXPECT_TRUE(response != nullptr);
}


}  // namespace ipc
}  // namespace ipc_server
