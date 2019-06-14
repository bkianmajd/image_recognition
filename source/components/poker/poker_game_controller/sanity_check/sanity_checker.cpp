#include "components/poker/poker_game_controller/sanity_check/sanity_checker.h"

#include <unordered_set>

namespace poker {
namespace {
constexpr int kCounterThreshold = 1;

const Card kUnknown(CARD_VALUE_UNKNOWN, SUIT_UNKNOWN);
const Card kHidden(CARD_VALUE_HIDDEN, SUIT_HIDDEN);

bool CheckSetForUniquenessAndAdd(const Card& card,
                                 std::unordered_set<int>* set) {
  // ignore if card is hidden or unknown and always return true because the
  // caller is expecting true for pass condition
  if (card.value == CARD_VALUE_UNKNOWN) {
    return true;
  }
  if (card.value == CARD_VALUE_HIDDEN) {
    return true;
  }

  // Attempt to find to the set
  int id = CardToUniqueId(card);
  auto it = set->find(id);

  // If unique, add to the set and return true
  if (it == set->end()) {
    set->insert(id);
    return true;
  }

  return false;
}

}  // namespace

SanityCheck::SanityCheck()
    : counter_(0), counter_threshold_(kCounterThreshold), error_ss_() {}

std::string SanityCheck::ErrorStr() const { return error_ss_.str(); }

bool SanityCheck::Check(const GameModel& old_game_model,
                        GameModel* new_game_model) {
  // Congruency Test checks if unknown cards match unknown cards and hidden
  // cards match hidden cards
  if (!CongruencyTest(*new_game_model)) {
    error_ss_ << "congruency test failed: ";
    return FailReturn(old_game_model, new_game_model);
  }

  // Check if there is a new hand
  if (CheckForNewHand(old_game_model, *new_game_model)) {
    if (!NewHandSanityTest(*new_game_model)) {
      error_ss_ << "New hand test failed: ";
      return FailReturn(old_game_model, new_game_model);
    }
  }

  // Check if any of the hands are unique
  if (!CheckForDuplicates(*new_game_model)) {
    error_ss_ << "Duplicate cards detected: ";
    return FailReturn(old_game_model, new_game_model);
  }

  return true;
}

bool SanityCheck::NewHandSanityTest(const GameModel& game_model) const {
  // The dealer hands should be empty
  for (size_t i = DEALER_ONE; i < DEALER_MAX_SIZE; ++i) {
    if (game_model.dealer_cards[i] != kUnknown) {
      return false;
    }
  }

  return true;
}

bool SanityCheck::FailReturn(const GameModel& old_game_model,
                             GameModel* new_game_model) {
  *new_game_model = old_game_model;
  counter_++;

  if (counter_ > counter_threshold_) {
    error_ss_ << "counter over threshold: " << counter_ << std::endl;
    return false;
  }

  // Not over threshold so just use the last good model
  return true;
}

bool SanityCheck::PassReturn() {
  counter_ = 0;
  error_ss_.clear();
  return true;
}

bool SanityCheck::CheckForDuplicates(const GameModel& new_game_model) const {
  std::unordered_set<int> set;

  // Check if all player hands are unique
  for (size_t i = 0; i < new_game_model.player_hands.size(); ++i) {
    const PlayerHand& player_hand = new_game_model.player_hands[i];
    if (!CheckSetForUniquenessAndAdd(player_hand.FirstCard(), &set)) {
      return false;
    }

    if (!CheckSetForUniquenessAndAdd(player_hand.SecondCard(), &set)) {
      return false;
    }
  }

  // Check if all dealer cards are unique
  for (size_t i = DEALER_ONE; i < DEALER_MAX_SIZE; ++i) {
    const Card& dealer_hand = new_game_model.dealer_cards[i];
    if (!CheckSetForUniquenessAndAdd(dealer_hand, &set)) {
      return false;
    }
  }

  return true;
}

bool SanityCheck::CongruencyTest(const GameModel& new_game_model) const {
  for (size_t i = 0; i < new_game_model.player_hands.size(); ++i) {
    const PlayerHand& player_hand = new_game_model.player_hands[i];

    // Checking if all the player hands match when unknown
    if (player_hand.FirstCard() == kUnknown ||
        player_hand.SecondCard() == kUnknown) {
      if (player_hand.SecondCard() != kUnknown) {
        return false;
      }
      if (player_hand.FirstCard() != kUnknown) {
        return false;
      }
    }

    // Checking if all the player hands match when hidden
    if (player_hand.FirstCard() == kHidden ||
        player_hand.SecondCard() == kHidden) {
      if (player_hand.SecondCard() != kHidden) {
        return false;
      }
      if (player_hand.FirstCard() != kHidden) {
        return false;
      }
    }
  }  // for loop
  return true;
}

}  // namespace poker
