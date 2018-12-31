#include "components/poker/poker_game_controller/landmark_finder/card_reader/card_reader.h"

#include <iostream>

#include "gtest/gtest.h"
#include "helpers/file_manager/file_manager.h"

namespace poker {
namespace {

const std::string kTestingdDirectory =
    "components/poker/poker_game_controller/landmark_finder/card_reader/"
    "test_data";

const std::string kSuitOutput = "suit_output.jpg";
const std::string kValueOutput = "value_output.jpg";
}  // namespace

class CardReaderTest : public testing::Test {
 public:
  CardReaderTest()
      : directory_finder_(
            helpers::CreateDirectoryFinderFromWorkspace(kTestingdDirectory)) {}

  void TestCard(const std::string& card_file, Card expected_card) {
    std::vector<char> bytes = helpers::FileManager::ReadFile(
        directory_finder_.GetAbsPathOfTargetFile(card_file));
    Card card = card_reader_.ConvertToCard(bytes);
    EXPECT_EQ(card.suit, expected_card.suit);
    EXPECT_EQ(card.value, expected_card.value);

    ASSERT_GT(card_reader_.suit_.size(), 0);
    ASSERT_GT(card_reader_.value_.size(), 0);

    // output suit
    EXPECT_TRUE(helpers::FileManager::StoreFile(
        card_reader_.suit_.data(), card_reader_.suit_.size(),
        directory_finder_.GetAbsPathOfTargetFile(kSuitOutput)));
    // output value
    EXPECT_TRUE(helpers::FileManager::StoreFile(
        card_reader_.value_.data(), card_reader_.value_.size(),
        directory_finder_.GetAbsPathOfTargetFile(kValueOutput)));
  }

 protected:
  helpers::DirectoryFinder directory_finder_;
  CardReader card_reader_;
};

TEST_F(CardReaderTest, ConstructDestruct) {}

TEST_F(CardReaderTest, AreaTest) {
  TestCard("ace_clubs_hand.jpg", Card(CARD_VALUE_ACE, SUIT_CLUB));
  TestCard("ace_hearts_hand.jpg", Card(CARD_VALUE_ACE, SUIT_HEART));
  TestCard("queen_clubs_hand.jpg", Card(CARD_VALUE_QUEEN, SUIT_CLUB));
  TestCard("ten_diamonds_table.jpg", Card(CARD_VALUE_TEN, SUIT_DIAMOND));
  TestCard("five_diamonds_table.jpg", Card(CARD_VALUE_FIVE, SUIT_DIAMOND));
  TestCard("ten_clubs_table.jpg", Card(CARD_VALUE_TEN, SUIT_CLUB));
  TestCard("ace_spades_table.jpg", Card(CARD_VALUE_ACE, SUIT_SPADE));
  TestCard("two_hearts_hand.jpg", Card(CARD_VALUE_TWO, SUIT_HEART));

}

}  // namespace poker
