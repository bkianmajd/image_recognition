#include "components/poker/statistics/statistic_calculator.h"

#include <iostream>

#include "gtest/gtest.h"

namespace poker {

class StatisticsTest : public testing::Test {
public:
StatisticsTest() {}

protected:
StatisticCalculator statistics_calculator_;

};
TEST_F(StatisticsTest, ConstructDestruct) {}

}  // namespace poker

