#ifndef TEST_COMMAND_H_
#define TEST_COMMAND_H_

#include <iostream>
#include "image_ipc/icommand.h"
#include "image_ipc/responses/ack_response.h"

namespace ipc {

class TestCommand : public ICommand {
 public:
  virtual ~TestCommand() {}

  std::unique_ptr<IResponse> ApplyCommand() override {
    std::cout << "Running test command" << std::endl;

    return (std::unique_ptr<IResponse>(new AckResponse(true)));
  }
};

}  // namespace ipc

#endif  // TEST_COMMAND_H_
