#include <iostream>

#include <QCoreApplication>
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  ::testing::InitGoogleTest(&argc, argv);

  std::cout << "Running all tests:" << std::endl;
  bool testsPassed = RUN_ALL_TESTS();

  return testsPassed;
}
