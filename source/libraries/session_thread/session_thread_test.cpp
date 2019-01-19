#include "libraries/session_thread/session_thread.h"

#include <iostream>

#include "gtest/gtest.h"

class TestClass {
 public:
  TestClass() = default;

  void PrintTest() {
    std::cout << "test" << std::endl;
    std::flush(std::cout);
  }
};

class SessionThreadTest : public testing::Test {
 public:
  SessionThreadTest() {}

 protected:
  SessionThread<TestClass> test_class_thread_;
};

TEST_F(SessionThreadTest, ConstructDestruct) {}

TEST_F(SessionThreadTest, StartAndEndTest) {
  test_class_thread_.StartSession<TestClass>();

  test_class_thread_.task_runner()->PostTask(
      FROM_HERE, base::Bind(&TestClass::PrintTest,
                            base::Unretained(test_class_thread_.get())));
  test_class_thread_.EndSessionAndJoin();
}
