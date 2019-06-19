#include "components/poker/simulator/defs/point_calculator.h"

#include <cassert>

namespace poker {
namespace simulator {
namespace {

// returns an integer with a value or kFalse;
constexpr int kFalse = -2;
constexpr int kUnknown = 0;

bool CustomSort(const Card& lhs, const Card& rhs) {
  if (lhs.value == CARD_VALUE_ACE) {
    return false;
  }
  if (rhs.value == CARD_VALUE_ACE) {
    return true;
  }
  return lhs.value < rhs.value;
}

std::array<Card, 7> SortCardsByValue(
    const std::array<Card, 7>& unsorted_cards) {
  std::array<Card, 7> retVec(unsorted_cards);

  // Sorts smallest to largest, exception is ace - which gets stored as the
  // largest value
  std::sort(retVec.begin(), retVec.end(), CustomSort);
  return retVec;
}

std::unordered_map<CardValue, int> PopulateValueMap(
    const std::array<Card, 7>& cards) {
  // count the number of cards
  std::unordered_map<CardValue, int> value_map(7);
  for (size_t i = 0; i < cards.size(); ++i) {
    auto it = value_map.find(cards[i].value);
    if (it == value_map.end()) {
      value_map[cards[i].value] = 1;
    } else {
      int count = value_map[cards[i].value];
      value_map[cards[i].value] = count + 1;
    }
  }

  return value_map;
}

// Searches for 5 congruent cards starting at value
bool HasCongruentFive(CardValue value,
                      const std::unordered_map<CardValue, int>& value_map) {
  // Check for the first value
  if (value_map.find(value) == value_map.end()) {
    return false;
  }
  // At this point, map has the first value
  if (value_map.find(static_cast<CardValue>(value + 1)) == value_map.end()) {
    return false;
  }
  // At this point, map has the first & second value
  if (value_map.find(static_cast<CardValue>(value + 2)) == value_map.end()) {
    return false;
  }
  // At this point, map has the first & second & third value
  if (value_map.find(static_cast<CardValue>(value + 3)) == value_map.end()) {
    return false;
  }
  // At this point, map has the first & second & third & fourth value
  if (value_map.find(static_cast<CardValue>(value + 4)) == value_map.end()) {
    return false;
  }

  // The map has all five values
  return true;
}

bool HasPair(CardValue value,
             const std::unordered_map<CardValue, int>& value_map) {
  auto it = value_map.find(value);
  if (it == value_map.end()) {
    return false;
  }
  return it->second >= 2;
}

// Converts value to a minor point - which is hex
constexpr int GetMinorPoint(CardValue value) {
  switch (value) {
    case CARD_VALUE_ACE:
      return 0x0E;
    case CARD_VALUE_TWO:
      return 0x02;
    case CARD_VALUE_THREE:
      return 0x03;
    case CARD_VALUE_FOUR:
      return 0x04;
    case CARD_VALUE_FIVE:
      return 0x05;
    case CARD_VALUE_SIX:
      return 0x06;
    case CARD_VALUE_SEVEN:
      return 0x07;
    case CARD_VALUE_EIGHT:
      return 0x08;
    case CARD_VALUE_NINE:
      return 0x09;
    case CARD_VALUE_TEN:
      return 0x0A;
    case CARD_VALUE_JACK:
      return 0x0B;
    case CARD_VALUE_QUEEN:
      return 0x0C;
    case CARD_VALUE_KING:
      return 0x0D;
    default:
      return 0x00;
  }
}

// sorted cards are sorted from lowest to highest. Return from highest to
// lowest. e.g. ace [0] king[1]
template <typename Array>
void GetNextHighestCards(const std::vector<Card>& sorted_cards,
                         Array* highest_cards) {
  size_t sz = highest_cards->size();
  unsigned int storing_index = 0;

  auto high_card_it = sorted_cards.end();
  while (high_card_it > sorted_cards.begin()) {
    high_card_it--;

    // Prevent accessing greater than sz, indicates we're done populating into
    // highest_cards
    if (storing_index == sz) {
      return;
    }

    // store the next highest
    (*highest_cards)[storing_index] = *high_card_it;
    storing_index++;
  }
}

}  // namespace

PointCalculator::PointCalculator(const std::array<Card, 7>& unsorted_cards)
    : value_sorted_cards_(SortCardsByValue(unsorted_cards)),
      value_map_(PopulateValueMap(unsorted_cards)),
      flush_point_(kUnknown),
      straight_point_(kUnknown),
      three_of_kind_(CARD_VALUE_UNKNOWN),
      pair_(CARD_VALUE_UNKNOWN) {
  // The caller should not pass hidden or unknown cards
  for (size_t i = 0; i < unsorted_cards.size(); ++i) {
    assert(unsorted_cards[i].value != CARD_VALUE_UNKNOWN);
    assert(unsorted_cards[i].value != CARD_VALUE_HIDDEN);
    assert(unsorted_cards[i].suit != SUIT_UNKNOWN);
    assert(unsorted_cards[i].suit != SUIT_HIDDEN);
  }
}

Points PointCalculator::GetPoints() {
  // a 32 bit value is composed of 8 4 bit values
  // A poker hand is made up of 5 cards
  // The first 5 digits will be the minor point
  // THe 6th digit is the major point

  MinorPoint minor_point = RoyalFlush();
  if (minor_point != kFalse) {
    return 0xA00000;
  }

  minor_point = FourOfAKindAndUpdate();
  if (minor_point != kFalse) {
    return 0x900000 + minor_point;
  }

  minor_point = StraightFlushAndUpdate();
  if (minor_point != kFalse) {
    return 0x800000 + minor_point;
  }

  minor_point = FullHouse();
  if (minor_point != kFalse) {
    return 0x700000 + minor_point;
  }

  minor_point = Flush();
  if (minor_point != kFalse) {
    return 0x600000 + minor_point;
  }

  minor_point = Straight();
  if (minor_point != kFalse) {
    return 0x500000 + minor_point;
  }

  minor_point = ThreeOfAKind();
  if (minor_point != kFalse) {
    return 0x400000 + minor_point;
  }

  minor_point = TwoPair();
  if (minor_point != kFalse) {
    return 0x300000 + minor_point;
  }

  minor_point = Pair();
  if (minor_point != kFalse) {
    return 0x200000 + minor_point;
  }

  return HighCard();
}

PointCalculator::MinorPoint PointCalculator::RoyalFlush() const {
  // Check for royal straight
  if (!RoyalStraight()) {
    return kFalse;
  }

  int spade_counter = 0;
  int diamond_counter = 0;
  int club_counter = 0;
  int heart_counter = 0;

  auto it =
      std::lower_bound(value_sorted_cards_.begin(), value_sorted_cards_.end(),
                       Card(CARD_VALUE_TEN, SUIT_UNKNOWN), CustomSort);
  // you need a suit from start to end
  while (it != value_sorted_cards_.end()) {
    switch (it->suit) {
      case SUIT_CLUB:
        club_counter++;
        break;
      case SUIT_HEART:
        heart_counter++;
        break;
      case SUIT_SPADE:
        spade_counter++;
        break;
      case SUIT_DIAMOND:
        diamond_counter++;
        break;
      default:
        std::cerr << "this shouldn't happen" << std::endl;
        return kFalse;
    }
    it++;
  }
  if (spade_counter > 4 || club_counter > 4 || diamond_counter > 4 ||
      heart_counter > 4) {
    return GetMinorPoint(CARD_VALUE_ACE);
  }

  return kFalse;
}

PointCalculator::MinorPoint PointCalculator::FourOfAKindAndUpdate() {
  // Update Pair, Two Pair, and Three of Kind
  UpdatePair();
  if (pair_ == CARD_VALUE_HIDDEN) {
    three_of_kind_ = CARD_VALUE_HIDDEN;
    return kFalse;
  }

  UpdateThreeOfKind();
  if (three_of_kind_ == CARD_VALUE_HIDDEN) {
    return kFalse;
  }

  // By now you have at least one three of a kind. You still need to search for
  // all four of a kind possibilities because you may run into this AAA 2222

  // There shall be only 4 of a kind in the hand so order doesn't matter
  CardValue four_value = CARD_VALUE_UNKNOWN;
  for (auto it = value_map_.begin(); it != value_map_.end(); ++it) {
    if (it->second == 4) {
      four_value = it->first;
      break;
    }
  }

  if (four_value == CARD_VALUE_UNKNOWN) {
    return kFalse;
  }

  // Get the next highest card that is not a four value
  auto it = value_sorted_cards_.end();
  it--;
  while (it->value == four_value) {
    it--;
  }
  return (four_value << 4) + GetMinorPoint(it->value);
}

PointCalculator::MinorPoint PointCalculator::StraightFlushAndUpdate() {
  // Update Straight and flush
  straight_point_ = Straight();
  flush_point_ = Flush();

  if (flush_point_ == kFalse || straight_point_ == kFalse) {
    return kFalse;
  }

  for (int i = static_cast<int>(CARD_VALUE_NINE);
       i >= static_cast<int>(CARD_VALUE_ACE); --i) {
    CardValue card_value = static_cast<CardValue>(i);
    if (HasCongruentFive(card_value, value_map_) &&
        HasFlushFromStraight(card_value)) {
      // HOLY! this guy just hit a straight flush. Return card + 4 (e.g. A + 4 =
      // 5)
      return GetMinorPoint(static_cast<CardValue>(i + 4));
    }
  }
  return kFalse;
}

PointCalculator::MinorPoint PointCalculator::FullHouse() const {
  if (three_of_kind_ == kUnknown) {
    // Technically should not be reached
    assert(false);
  }
  if (three_of_kind_ == CARD_VALUE_HIDDEN) {
    return kFalse;
  }

  // Convert the minor point to a card
  std::unordered_map<CardValue, Count> value_map_without_three(value_map_);
  value_map_without_three.erase(three_of_kind_);

  // Shift the minor point up by 4 (e.g. Aces full of kings ... would be 0xED)
  MinorPoint minorPoint = GetMinorPoint(three_of_kind_) << 4;

  // Find the next pair
  if (HasPair(CARD_VALUE_ACE, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_ACE);
  }
  if (HasPair(CARD_VALUE_KING, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_KING);
  }
  if (HasPair(CARD_VALUE_QUEEN, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_QUEEN);
  }
  if (HasPair(CARD_VALUE_JACK, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_JACK);
  }
  if (HasPair(CARD_VALUE_TEN, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_TEN);
  }
  if (HasPair(CARD_VALUE_NINE, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_NINE);
  }
  if (HasPair(CARD_VALUE_EIGHT, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_EIGHT);
  }
  if (HasPair(CARD_VALUE_SEVEN, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_SEVEN);
  }
  if (HasPair(CARD_VALUE_SIX, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_SIX);
  }
  if (HasPair(CARD_VALUE_FIVE, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_FIVE);
  }
  if (HasPair(CARD_VALUE_FOUR, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_FOUR);
  }
  if (HasPair(CARD_VALUE_THREE, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_THREE);
  }
  if (HasPair(CARD_VALUE_TWO, value_map_without_three)) {
    return minorPoint + GetMinorPoint(CARD_VALUE_TWO);
  }
  return kFalse;
}

bool PointCalculator::HasFlushFromStraight(CardValue cardValue) const {
  int spade_counter = 0;
  int club_counter = 0;
  int diamond_counter = 0;
  int heart_counter = 0;

  // Conotinue with the nominal algorithm:
  auto last_card = static_cast<CardValue>(static_cast<int>(cardValue + 4));
  auto it =
      std::lower_bound(value_sorted_cards_.begin(), value_sorted_cards_.end(),
                       Card(cardValue, SUIT_UNKNOWN), CustomSort);
  auto it_end =
      std::upper_bound(value_sorted_cards_.begin(), value_sorted_cards_.end(),
                       Card(last_card, SUIT_UNKNOWN), CustomSort);

  // there is an edge case when CardValue is an ace becuase ace is stored as the
  // highest value. In this case, you need to define two as your lower bound, 5
  // as your upper bound. And do one more count around ace
  if (cardValue == CARD_VALUE_ACE) {
    auto ace_it =
        std::lower_bound(value_sorted_cards_.begin(), value_sorted_cards_.end(),
                         Card(CARD_VALUE_ACE, SUIT_UNKNOWN), CustomSort);
    while (ace_it != value_sorted_cards_.end()) {
      switch (ace_it->suit) {
        case SUIT_CLUB:
          club_counter++;
          break;
        case SUIT_HEART:
          heart_counter++;
          break;
        case SUIT_SPADE:
          spade_counter++;
          break;
        case SUIT_DIAMOND:
          diamond_counter++;
          break;
        default:
          std::cerr << "this shouldn't happen" << std::endl;
          return false;
      }
      ace_it++;
    }
    // Redefine it at two
    it =
        std::lower_bound(value_sorted_cards_.begin(), value_sorted_cards_.end(),
                         Card(CARD_VALUE_TWO, SUIT_UNKNOWN), CustomSort);
  }

  // Scroll through between the lower and upper bound of your straight limit to
  // see if there is a flush
  while (it != it_end) {
    switch (it->suit) {
      case SUIT_CLUB:
        club_counter++;
        break;
      case SUIT_HEART:
        heart_counter++;
        break;
      case SUIT_SPADE:
        spade_counter++;
        break;
      case SUIT_DIAMOND:
        diamond_counter++;
        break;
      default:
        std::cerr << "this shouldn't happen" << std::endl;
        return false;
    }
    it++;
  }
  return (spade_counter > 4) || (club_counter > 4) || (diamond_counter > 4) ||
         (heart_counter > 4);
}

PointCalculator::MinorPoint PointCalculator::Flush() const {
  if (flush_point_ != kUnknown) {
    return flush_point_;
  }

  int spade_counter = 0;
  int club_counter = 0;
  int diamond_counter = 0;
  int heart_counter = 0;

  for (const Card& card : value_sorted_cards_) {
    switch (card.suit) {
      case SUIT_CLUB:
        club_counter++;
        break;
      case SUIT_HEART:
        heart_counter++;
        break;
      case SUIT_SPADE:
        spade_counter++;
        break;
      case SUIT_DIAMOND:
        diamond_counter++;
        break;
      default:
        std::cerr << "this shouldn't happen" << std::endl;
    }
  }
  Suit suit_lookup_value = SUIT_UNKNOWN;
  if (spade_counter >= 5) {
    suit_lookup_value = SUIT_SPADE;
  }

  if (club_counter >= 5) {
    suit_lookup_value = SUIT_CLUB;
  }

  if (diamond_counter >= 5) {
    suit_lookup_value = SUIT_DIAMOND;
  }

  if (heart_counter >= 5) {
    suit_lookup_value = SUIT_HEART;
  }

  if (suit_lookup_value == SUIT_UNKNOWN) {
    return kFalse;
  }

  // get the next 5 higest cards in the suit
  std::array<Card, 5> high_card_array{{CARD_VALUE_UNKNOWN, CARD_VALUE_UNKNOWN}};
  std::vector<Card> sorted_cards;
  for (size_t index = 0; index < value_sorted_cards_.size(); ++index) {
    // Skip this case
    if (value_sorted_cards_[index].suit != suit_lookup_value) {
      continue;
    }
    sorted_cards.push_back(value_sorted_cards_[index]);
  }
  GetNextHighestCards(sorted_cards, &high_card_array);

  return (GetMinorPoint(high_card_array[0].value) << 16) +
         (GetMinorPoint(high_card_array[1].value) << 12) +
         (GetMinorPoint(high_card_array[2].value) << 8) +
         (GetMinorPoint(high_card_array[3].value) << 4) +
         (GetMinorPoint(high_card_array[4].value) << 0);
}

bool PointCalculator::RoyalStraight() const {
  if (value_map_.find(CARD_VALUE_TEN) == value_map_.end()) {
    return false;
  }
  if (value_map_.find(CARD_VALUE_JACK) == value_map_.end()) {
    return false;
  }
  if (value_map_.find(CARD_VALUE_QUEEN) == value_map_.end()) {
    return false;
  }
  if (value_map_.find(CARD_VALUE_KING) == value_map_.end()) {
    return false;
  }
  if (value_map_.find(CARD_VALUE_ACE) == value_map_.end()) {
    return false;
  }
  return true;
}

PointCalculator::MinorPoint PointCalculator::Straight() const {
  if (straight_point_ != kUnknown) {
    return straight_point_;
  }

  if (RoyalStraight()) {
    return GetMinorPoint(CARD_VALUE_ACE);
  }

  // At this point - ace is the smallest of the value
  if (HasCongruentFive(CARD_VALUE_NINE, value_map_)) {
    return GetMinorPoint(CARD_VALUE_KING);
  }
  if (HasCongruentFive(CARD_VALUE_EIGHT, value_map_)) {
    return GetMinorPoint(CARD_VALUE_QUEEN);
  }
  if (HasCongruentFive(CARD_VALUE_SEVEN, value_map_)) {
    return GetMinorPoint(CARD_VALUE_JACK);
  }
  if (HasCongruentFive(CARD_VALUE_SIX, value_map_)) {
    return GetMinorPoint(CARD_VALUE_TEN);
  }
  if (HasCongruentFive(CARD_VALUE_FIVE, value_map_)) {
    return GetMinorPoint(CARD_VALUE_NINE);
  }
  if (HasCongruentFive(CARD_VALUE_FOUR, value_map_)) {
    return GetMinorPoint(CARD_VALUE_EIGHT);
  }
  if (HasCongruentFive(CARD_VALUE_THREE, value_map_)) {
    return GetMinorPoint(CARD_VALUE_SEVEN);
  }
  if (HasCongruentFive(CARD_VALUE_TWO, value_map_)) {
    return GetMinorPoint(CARD_VALUE_SIX);
  }
  if (HasCongruentFive(CARD_VALUE_ACE, value_map_)) {
    return GetMinorPoint(CARD_VALUE_FIVE);
  }
  return kFalse;
}

PointCalculator::MinorPoint PointCalculator::ThreeOfAKind() const {
  if (three_of_kind_ == CARD_VALUE_UNKNOWN) {
    std::cerr << "this should not happen" << std::endl;
    assert(false);
  }
  if (three_of_kind_ == CARD_VALUE_HIDDEN) {
    return kFalse;
  }

  // get the next 2 higest cards excluding the three of a kind
  std::array<Card, 2> high_card_array{{CARD_VALUE_UNKNOWN, CARD_VALUE_UNKNOWN}};
  std::vector<Card> sorted_cards;
  for (size_t index = 0; index < value_sorted_cards_.size(); ++index) {
    // Skip this case
    if (value_sorted_cards_[index].value == three_of_kind_) {
      continue;
    }
    sorted_cards.push_back(value_sorted_cards_[index]);
  }
  GetNextHighestCards(sorted_cards, &high_card_array);

  // Now shift the current three of a kind by 3 digits and put the first 2 cards
  // in the other two digits
  MinorPoint minor_point = GetMinorPoint(three_of_kind_);  // this is 4 bits
  // 0x0E on a big endian system this is 0x0E0000 which is why this wont work on
  // those systems
  minor_point = (minor_point << 8) +
                (GetMinorPoint(high_card_array[0].value) << 4) +
                GetMinorPoint(high_card_array[1].value);
  return minor_point;
}

PointCalculator::MinorPoint PointCalculator::TwoPair() const {
  // Should return the top two pairs.
  // a 2 pair value system should consist of the highest pair followed by the
  // next highest. e.g. C 2
  if (pair_ == CARD_VALUE_UNKNOWN) {
    std::cerr << "this should not happen" << std::endl;
    assert(false);
  }

  // Get the highest pair
  if (pair_ == CARD_VALUE_HIDDEN) {
    return kFalse;
  }

  // Remove the highest pair so we dont count it twice
  std::unordered_map<CardValue, Count> modified_value_map(value_map_);
  CardValue first_pair = pair_;
  modified_value_map.erase(first_pair);

  // fill in the first column
  CardValue second_pair = CARD_VALUE_UNKNOWN;
  if (HasPair(CARD_VALUE_ACE, modified_value_map)) {
    second_pair = CARD_VALUE_ACE;
  }
  // The for loop does the following statement above... just in a generic way
  for (CardValue value = CARD_VALUE_KING;
       value != CARD_VALUE_ACE && second_pair == CARD_VALUE_UNKNOWN;
       value = static_cast<CardValue>(static_cast<int>(value) - 1)) {
    if (HasPair(value, modified_value_map)) {
      second_pair = value;
      break;
    }
  }

  if (second_pair == CARD_VALUE_UNKNOWN) {
    return kFalse;
  }

  // Now find the highest card that are not the two pairs
  std::array<Card, 1> high_card_array;
  std::vector<Card> next_highest_cards;
  for (size_t index = 0; index < value_sorted_cards_.size(); ++index) {
    // Skip this case
    if (value_sorted_cards_[index].value == first_pair) {
      continue;
    }
    // Skip this case
    if (value_sorted_cards_[index].value == second_pair) {
      continue;
    }
    next_highest_cards.push_back(value_sorted_cards_[index]);
  }
  GetNextHighestCards(next_highest_cards, &high_card_array);

  // Move the hex value 2 digits over
  return (GetMinorPoint(first_pair) << 8) + (GetMinorPoint(second_pair) << 4) +
         GetMinorPoint(high_card_array[0].value);
}

PointCalculator::MinorPoint PointCalculator::Pair() const {
  if (pair_ == CARD_VALUE_UNKNOWN) {
    std::cerr << "this should not happen" << std::endl;
    assert(false);
  }

  if (pair_ == CARD_VALUE_HIDDEN) {
    return kFalse;
  }

  // Now find the next 3 highest cards
  std::array<Card, 3> high_card_array;
  std::vector<Card> next_highest_cards;
  for (size_t index = 0; index < value_sorted_cards_.size(); ++index) {
    // Skip this case
    if (value_sorted_cards_[index].value == pair_) {
      continue;
    }
    next_highest_cards.push_back(value_sorted_cards_[index]);
  }
  GetNextHighestCards(next_highest_cards, &high_card_array);

  // Move the hex value 3 digits over
  return (GetMinorPoint(pair_) << 12) +
         (GetMinorPoint(high_card_array[0].value) << 8) +
         (GetMinorPoint(high_card_array[1].value) << 4) +
         GetMinorPoint(high_card_array[2].value);
}

PointCalculator::MinorPoint PointCalculator::HighCard() const {
  std::array<Card, 5> high_card_array;
  std::vector<Card> value_sorted_cards(value_sorted_cards_.begin(),
                                       value_sorted_cards_.end());

  GetNextHighestCards(value_sorted_cards, &high_card_array);
  return (GetMinorPoint(high_card_array[0].value) << 16) +
         (GetMinorPoint(high_card_array[1].value) << 12) +
         (GetMinorPoint(high_card_array[2].value) << 8) +
         (GetMinorPoint(high_card_array[3].value) << 4) +
         GetMinorPoint(high_card_array[4].value);
}

void PointCalculator::UpdatePair() {
  // Returns the highest pair found
  if (HasPair(CARD_VALUE_ACE, value_map_)) {
    pair_ = CARD_VALUE_ACE;
    return;
  }
  // The for loop does the following statement above... just in a generic way
  for (CardValue value = CARD_VALUE_KING; value != CARD_VALUE_ACE;
       value = static_cast<CardValue>(static_cast<int>(value) - 1)) {
    if (HasPair(value, value_map_)) {
      pair_ = value;
      return;
    }
  }
  pair_ = CARD_VALUE_HIDDEN;
}

void PointCalculator::UpdateThreeOfKind() {
  // This returns the first three of a kind. However, if there are 2 three of
  // a kinds, then a full house should be used.
  auto it = value_map_.find(CARD_VALUE_ACE);
  if (it != value_map_.end()) {
    if (it->second >= 3) {
      three_of_kind_ = CARD_VALUE_ACE;
      return;
    }
  }

  for (int i = static_cast<int>(CARD_VALUE_KING);
       i != static_cast<int>(CARD_VALUE_ACE); --i) {
    it = value_map_.find(static_cast<CardValue>(i));
    if (it == value_map_.end()) {
      continue;
    }
    if (it->second >= 3) {
      three_of_kind_ = it->first;
      return;
    }
  }

  three_of_kind_ = CARD_VALUE_HIDDEN;
}

}  // namespace simulator
}  // namespace poker
