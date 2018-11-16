#include "libraries/model_generator/poker_model_generator/poker_model_generator.h"
#include "libraries/model_generator/poker_model_generator/poker_model_generator_mock.hpp"

#include <iostream>

#include "gtest/gtest.h"

namespace image_recognition {
namespace poker {

class PokerModelGeneratorTest : public testing::Test {
 public:
  PokerModelGeneratorTest() {}

 protected:
  PokerModelGenerator poker_model_generator_;
};

TEST_F(PokerModelGeneratorTest, ConstructDestruct) {}

}  // namespace poker
}  // namespace image_recognition
