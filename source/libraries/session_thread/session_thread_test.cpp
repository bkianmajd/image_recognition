#include "libraries/session_thread/session_thread.h"

#include <iostream>

#include "gtest/gtest.h"

class TestFoo {
 public:
  TestFoo() = default;
};

class TestClass {
 public:
  TestClass(const TestFoo& test1, const TestFoo& test2)
      : test1_(test1), test2_(test2) {}

  void PrintTest() {
    std::cout << "test" << std::endl;
    std::flush(std::cout);
  }

 private:
  TestFoo test1_;
  TestFoo test2_;
};

class SessionThreadTest : public testing::Test {
 public:
  SessionThreadTest() {}

 protected:
  SessionThread<TestClass> test_class_thread_;
};

TEST_F(SessionThreadTest, ConstructDestruct) {}

TEST_F(SessionThreadTest, StartAndEndTest) {
  TestFoo test1;
  TestFoo test2;
  test_class_thread_.StartSession<TestClass>(test1, test2);

  test_class_thread_.task_runner()->PostTask(
      FROM_HERE, base::Bind(&TestClass::PrintTest,
                            base::Unretained(test_class_thread_.get())));
  test_class_thread_.EndSessionAndJoin();
}
