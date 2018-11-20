#include <iostream>

#include <QApplication>
#include <QCoreApplication>
#include <thread>
#include "gtest/gtest.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  // has to be started from this thread
  ::testing::InitGoogleTest(&argc, argv);

  bool testsPassed = RUN_ALL_TESTS();


  // Run the qt message loops
  // a.exec();


  // a->quit();
  return testsPassed;
}
