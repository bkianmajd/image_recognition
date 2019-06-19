#ifndef PREFLOP_SIMILAR_CHECKER_H_
#define PREFLOP_SIMILAR_CHECKER_H_

#include "components/poker/entities/card_def.h"

#include <cassert>
#include <set>
#include "gtest/gtest_prod.h"

namespace poker {
namespace statistics {
namespace {

// returns same combos with different suits. e.g. A heart, king diamond is
// similar to A diamond K hearts
std::vector<PlayerHand> GetDifferentSuitSimalrities(CardValue card_value1,
                                                    CardValue card_value2) {
  std::vector<PlayerHand> similar_hands;
  // First card is heart
  similar_hands.emplace_back(Card(card_value1, SUIT_HEART),
                             Card(card_value2, SUIT_DIAMOND));
  similar_hands.emplace_back(Card(card_value1, SUIT_HEART),
                             Card(card_value2, SUIT_CLUB));
  similar_hands.emplace_back(Card(card_value1, SUIT_HEART),
                             Card(card_value2, SUIT_SPADE));

  // First card is diamond
  similar_hands.emplace_back(Card(card_value1, SUIT_DIAMOND),
                             Card(card_value2, SUIT_HEART));
  similar_hands.emplace_back(Card(card_value1, SUIT_DIAMOND),
                             Card(card_value2, SUIT_CLUB));
  similar_hands.emplace_back(Card(card_value1, SUIT_DIAMOND),
                             Card(card_value2, SUIT_SPADE));

  // First card is club
  similar_hands.emplace_back(Card(card_value1, SUIT_CLUB),
                             Card(card_value2, SUIT_HEART));
  similar_hands.emplace_back(Card(card_value1, SUIT_CLUB),
                             Card(card_value2, SUIT_DIAMOND));
  similar_hands.emplace_back(Card(card_value1, SUIT_CLUB),
                             Card(card_value2, SUIT_SPADE));

  // First card is spade
  similar_hands.emplace_back(Card(card_value1, SUIT_SPADE),
                             Card(card_value2, SUIT_HEART));
  similar_hands.emplace_back(Card(card_value1, SUIT_SPADE),
                             Card(card_value2, SUIT_DIAMOND));
  similar_hands.emplace_back(Card(card_value1, SUIT_SPADE),
                             Card(card_value2, SUIT_CLUB));
  return similar_hands;
}

std::vector<PlayerHand> GetSameSuitSimilarities(CardValue card_value1,
                                                CardValue card_value2) {
  assert(card_value1 != card_value2);
  std::vector<PlayerHand> similar_hands;
  similar_hands.emplace_back(Card(card_value1, SUIT_HEART),
                             Card(card_value2, SUIT_HEART));
  similar_hands.emplace_back(Card(card_value1, SUIT_DIAMOND),
                             Card(card_value2, SUIT_DIAMOND));
  similar_hands.emplace_back(Card(card_value1, SUIT_CLUB),
                             Card(card_value2, SUIT_CLUB));
  similar_hands.emplace_back(Card(card_value1, SUIT_SPADE),
                             Card(card_value2, SUIT_SPADE));

  return similar_hands;
}

}  // namespace

/// Locates hands that have similar preflop statistics
class PreflopSimilarities {
 public:
  PreflopSimilarities() {}

  // returns all hands similar
  std::vector<PlayerHand> GetSimilarities(const PlayerHand& player_hand) const {
    std::vector<PlayerHand> similar_hands;
    // Check if same suit
    if (player_hand.FirstCard().suit == player_hand.SecondCard().suit) {
      similar_hands = GetSameSuitSimilarities(player_hand.FirstCard().value,
                                              player_hand.SecondCard().value);
    } else {
      similar_hands = GetDifferentSuitSimalrities(
          player_hand.FirstCard().value, player_hand.SecondCard().value);
    }
    // get similar hands and remove player hand from vector, have to itterate
    // twice, one at each order
    Cleanse(player_hand, &similar_hands);
    CleanseUniqueId(&similar_hands);
    return similar_hands;
  }

 private:
  FRIEND_TEST(PreflopSimilaritiesTest, CleanseTest);
  FRIEND_TEST(PreflopSimilaritiesTest, CleanseUniqueIdTest);

  void Cleanse(const PlayerHand& hand_to_cleanse,
               std::vector<PlayerHand>* player_hands) const {
    CardsId unique_id = hand_to_cleanse.UniqueId();
    // remove hand from player_hands
    auto it = player_hands->begin();
    while (it != player_hands->end()) {
      if (it->UniqueId() == unique_id) {
        player_hands->erase(it);
        continue;
      }
      it++;
    }
  }

  // Ensures vector is unique
  void CleanseUniqueId(std::vector<PlayerHand>* player_hands) const {
    std::set<CardsId> unique_set;
    auto it = player_hands->begin();
    while (it != player_hands->end()) {
      auto unique_it = unique_set.find(it->UniqueId());
      // add to unique set if not inside
      if (unique_it == unique_set.end()) {
        unique_set.insert(it->UniqueId());
        it++;
        continue;
      }

      // remove from player_hands if found to be not unique
      player_hands->erase(it);
    }
  }
};

}  // namespace statistics
}  // namespace poker

#endif  // PREFLOP_SIMILAR_CHECKER_H_
