#ifndef STATISTICS_H_
#define STATISTICS_H_

// http://pi.math.cornell.edu/~mec/2006-2007/Probability/Texasholdem.pdf

#include <cassert>
#include <unordered_map>
#include <unordered_set>

#include "components/poker/entities/game_model_def.h"

namespace poker {

/// Returns probabilities
class StatisticCalculator {
 public:
  StatisticCalculator();

  /// All probabilities are calculated on the game model stored
  void UpdateGameModel(const GameModel& game_model);

  /// Calculates the probability that the card comes on the next turn
  double CalculateProbability(Card card) const;

  /// Calculates the probability that the suit comes on the next turn
  double CalculateProbability(Suit suit) const;

  /// Calculates the probability that the value comes on the next turn
  double CalculateProbability(CardValue value) const;

  /// Calculates the probability that the value comes at least once
  double CalculateProbabilityAtLeastOnce(CardValue value) const;

  /// Calculates the probability that the card comes at least once
  double CalculateProbabilityAtLeastOnce(Card card) const;

  /// Calculates the probability that the suit comes at least once
  double CalculateProbabilityAtLeastOnce(Suit suit) const;

 private:
  struct EnumHash {
    template <typename T>
    int operator()(T t) const {
      return static_cast<int>(t);
    }
  };

  void AddCardToSet(const Card& card);

  // These can be const and constructed every new game model
  std::unordered_set<int> active_cards_;
  std::unordered_map<Suit, int, EnumHash> suit_counter_;
  std::unordered_map<CardValue, int, EnumHash> value_counter_;
  int cards_remaining_;
  // How many cards the dealer has to flip over
  int turns_left_;
};

}  // namespace poker

#endif  // STATISTICS_H_
