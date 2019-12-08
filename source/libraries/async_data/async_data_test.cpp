#include "libraries/async_data/async_data.h"

#include <atomic>
#include <iostream>
#include <thread>

#include "gtest/gtest.h"

struct TestStruct {
  int x;
  std::array<double, 50> y;
};

class AsyncDataTest : public testing::Test {
 public:
  AsyncDataTest() {}

  TestStruct GetTestStruct() {
    TestStruct exp_str;
    exp_str.x = 1;
    exp_str.y.fill(50.2);
    return exp_str;
  }

  void Producer() {
    TestStruct exp_str = GetTestStruct();
    for (int i = 0; i < 99999; ++i) {
      async_data_.Write(exp_str);
      started_.store(true);
    }
    started_.store(false);
  }

 protected:
  AsyncData<TestStruct> async_data_;
  std::atomic_bool started_;
};

TEST_F(AsyncDataTest, ConstructDestruct) {}

TEST_F(AsyncDataTest, StartAndEndTest) {
  TestStruct exp_str = ;
  async_data_.Write(exp_str);
  TestStruct str = async_data_.Read();
  EXPECT_EQ(exp_str.x, str.x);
  EXPECT_EQ(exp_str.y, str.y);
}

TEST_F(AsyncDataTest, ThreadSafeTest) {
  started_.store(false);
  TestStruct exp_str = GetTestStruct();
  std::thread t1(&AsyncDataTest::Producer, this);

  // Thread hasn't started yet
  while(!started_.load()) {
    usleep(10);
  }

  // Thread is populating
  int runs = 0;
  while(started_.load()) {
    TestStruct str = async_data_.Read();
    EXPECT_EQ(exp_str.x, str.x);
    EXPECT_EQ(exp_str.y, str.y);
    runs++;
  }
  EXPECT_GT(runs, 0);
  t1.join();
}
