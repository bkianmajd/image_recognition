#include <iostream>

#include <QCoreApplication>
#include <thread>
#include "gtest/gtest.h"

void RunTest(QCoreApplication* a, bool* testsPassed) {
  std::cout << "Running all tests:" << std::endl;

  *testsPassed = RUN_ALL_TESTS();
  a->quit();
}

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  // has to be started from this thread
  ::testing::InitGoogleTest(&argc, argv);

  bool testsPassed = false;
  std::thread t1(RunTest, &a, &testsPassed);

  // Run the qt message loops
  a.exec();

  // Destory thread
  t1.join();

  return testsPassed;
}
