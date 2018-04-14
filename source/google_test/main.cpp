#include <iostream>

#include "gtest/gtest.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    std::cout << "Running all tests:" << std::endl;
    bool testsPassed = RUN_ALL_TESTS();

    return testsPassed;
}
