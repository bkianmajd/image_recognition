#include "components/poker/poker_game_controller/landmark_finder/area_finder/area_finder.h"

#include <iostream>

#include "components/poker/poker_game_controller/landmark_finder/area_finder/six_player_area_finder.h"
#include "gtest/gtest.h"

namespace poker {

class AreaFinderTest : public testing::Test {
 public:
  AreaFinderTest() {}

 protected:
  SixPlayerAreaFinder six_player_area_finder_;
};

TEST_F(AreaFinderTest, ConstructDestruct) {}

TEST_F(AreaFinderTest, FindAreaTest) {
  template_recognition::ScreenArea screen_area =
      six_player_area_finder_.GetCardAreaLeft(
          PlayerLocation::PLAYERLOC_PLAYER_ZERO);
  EXPECT_GT(screen_area.height, 0);
  EXPECT_GT(screen_area.width, 0);
}

}  // namespace poker
