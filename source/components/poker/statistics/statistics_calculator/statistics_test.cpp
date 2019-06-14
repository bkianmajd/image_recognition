#include "components/poker/statistics/statistic_calculator.h"

#include <iostream>

#include "gtest/gtest.h"

namespace poker {
namespace {
constexpr double kNearTolerance = .01;
}  // namespace

class StatisticsTest : public testing::Test {
 public:
  StatisticsTest() {}

 protected:
  StatisticCalculator statistics_calculator_;
};
TEST_F(StatisticsTest, ConstructDestruct) {}

TEST_F(StatisticsTest, CalculateSingleProb) {
  // Create game model
  GameModel game_model;
  statistics_calculator_.UpdateGameModel(game_model);

  // Card should be empty
  double p = statistics_calculator_.CalculateProbability(
      Card(CARD_VALUE_ACE, SUIT_CLUB));
  EXPECT_EQ(p, 1.0 / 52.0);

  // Put aces in players hand
  game_model.player_hands[PLAYERLOC_PLAYER_ZERO].FirstCard() =
      Card(CARD_VALUE_ACE, SUIT_HEART);
  game_model.player_hands[PLAYERLOC_PLAYER_ZERO].SecondCard() =
      Card(CARD_VALUE_ACE, SUIT_DIAMOND);
  statistics_calculator_.UpdateGameModel(game_model);
  p = statistics_calculator_.CalculateProbability(
      Card(CARD_VALUE_ACE, SUIT_CLUB));
  EXPECT_EQ(p, 1.0 / 50.0);

  // Put Ace of club in player hand and expect 0%
  game_model.player_hands[PLAYERLOC_PLAYER_ZERO].FirstCard() =
      Card(CARD_VALUE_ACE, SUIT_CLUB);
  statistics_calculator_.UpdateGameModel(game_model);
  p = statistics_calculator_.CalculateProbability(
      Card(CARD_VALUE_ACE, SUIT_CLUB));
  EXPECT_EQ(p, 0);
}

TEST_F(StatisticsTest, CalculateAtleastOne) {
  // Create game model
  GameModel game_model;

  // Put 4 cards in dealer hand
  game_model.dealer_cards[DEALER_ONE] = Card(CARD_VALUE_ACE, SUIT_CLUB);
  game_model.dealer_cards[DEALER_TWO] = Card(CARD_VALUE_TWO, SUIT_CLUB);
  game_model.dealer_cards[DEALER_THREE] = Card(CARD_VALUE_THREE, SUIT_CLUB);
  game_model.dealer_cards[DEALER_FOUR] = Card(CARD_VALUE_FOUR, SUIT_CLUB);
  statistics_calculator_.UpdateGameModel(game_model);

  // There should be one left
  double p = statistics_calculator_.CalculateProbabilityAtLeastOnce(
      Card(CARD_VALUE_ACE, SUIT_HEART));
  EXPECT_NEAR(p, 1.0 / 48.0, kNearTolerance);
}

TEST_F(StatisticsTest, CalculateFlush) {
  // Create game model
  GameModel game_model;

  // Put 3 cards in dealer hand and 2 hearts in player hand
  game_model.dealer_cards[DEALER_ONE] = Card(CARD_VALUE_ACE, SUIT_CLUB);
  game_model.dealer_cards[DEALER_TWO] = Card(CARD_VALUE_TWO, SUIT_HEART);
  game_model.dealer_cards[DEALER_THREE] = Card(CARD_VALUE_THREE, SUIT_HEART);
  game_model.player_hands[PLAYERLOC_PLAYER_ZERO].FirstCard() =
      Card(CARD_VALUE_FOUR, SUIT_HEART);
  game_model.player_hands[PLAYERLOC_PLAYER_ZERO].SecondCard() =
      Card(CARD_VALUE_FIVE, SUIT_HEART);
  statistics_calculator_.UpdateGameModel(game_model);

  // There should be the turn and river left and aprox 35%
  double p = statistics_calculator_.CalculateProbabilityAtLeastOnce(SUIT_HEART);
  EXPECT_NEAR(p, .35, .01);
}

TEST_F(StatisticsTest, CalculateStrait) {
  // Create game model
  GameModel game_model;

  // Put 3 cards in dealer hand and 2 hearts in player hand
  game_model.dealer_cards[DEALER_ONE] = Card(CARD_VALUE_ACE, SUIT_CLUB);
  game_model.dealer_cards[DEALER_TWO] = Card(CARD_VALUE_TWO, SUIT_HEART);
  game_model.dealer_cards[DEALER_THREE] = Card(CARD_VALUE_THREE, SUIT_HEART);
  game_model.player_hands[PLAYERLOC_PLAYER_ZERO].FirstCard() =
      Card(CARD_VALUE_FOUR, SUIT_HEART);
  game_model.player_hands[PLAYERLOC_PLAYER_ZERO].SecondCard() =
      Card(CARD_VALUE_FIVE, SUIT_HEART);
  statistics_calculator_.UpdateGameModel(game_model);

  // There should be the turn and river left looking for at least one 6
  double p =
      statistics_calculator_.CalculateProbabilityAtLeastOnce(CARD_VALUE_SIX);
  EXPECT_NEAR(p, .16, .01);
}

}  // namespace poker
