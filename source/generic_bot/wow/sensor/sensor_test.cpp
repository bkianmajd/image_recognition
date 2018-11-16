#include "generic_bot/wow/sensor/sensor_manager.h"

#include <iostream>

#include "gtest/gtest.h"

namespace bot {
namespace wow {

class SensorManagerTest : public testing::Test {
 public:
  SensorManagerTest()
      : directory_finder_(
            "wow_template_data",
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        sensor_manager_(directory_finder_) {}

 protected:
  helpers::DirectoryFinder directory_finder_;
  SensorManager sensor_manager_;
};

TEST_F(SensorManagerTest, ConstructDestruct) {}

}  // namespace sensor
}  // namespace bot
