#include "components/poker/poker_game_controller/landmark_finder/landmark_finder.h"

#include <iostream>

#include "gtest/gtest.h"

namespace poker {

class LandmarkFinderTest : public testing::Test {
 public:
  LandmarkFinderTest() : landmark_finder_(6) {}

 protected:
  LandmarkFinder landmark_finder_;
};
TEST_F(LandmarkFinderTest, ConstructDestruct) {}

}  // namespace poker
