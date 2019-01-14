#include "components/poker/workflow_session_thread.h"

#include <iostream>

#include "gtest/gtest.h"

namespace poker {

class WorkflowSessionThreadTest : public testing::Test {
 public:
  WorkflowSessionThreadTest() {}

 protected:
  WorkflowSessionThread workflow_session_thread_;
};

TEST_F(WorkflowSessionThreadTest, ConstructDestruct) {}

TEST_F(WorkflowSessionThreadTest, StartThread) {
  std::cout << "starting thread" << std::endl;
  EXPECT_TRUE(workflow_session_thread_.StartSession());
  std::cout << "starting thread complete" << std::endl;
  std::flush(std::cout);

  EXPECT_TRUE(workflow_session_thread_.EndSessionAndJoin());
}

TEST_F(WorkflowSessionThreadTest, StartThreadTwice) {
  std::cout << "starting thread" << std::endl;
  EXPECT_TRUE(workflow_session_thread_.StartSession());
  std::cout << "starting thread complete" << std::endl;
  std::flush(std::cout);
  EXPECT_TRUE(workflow_session_thread_.EndSessionAndJoin());

  std::cout << "starting thread" << std::endl;
  EXPECT_TRUE(workflow_session_thread_.StartSession());
  std::cout << "starting thread complete" << std::endl;
  std::flush(std::cout);
  EXPECT_TRUE(workflow_session_thread_.EndSessionAndJoin());
}

}  // namespace poker
