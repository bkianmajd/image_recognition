#ifndef SANITY_CHECK_H_
#define SANITY_CHECK_H_

#include <sstream>
#include <string>

#include "components/poker/entities/comparator/comparator.h"
#include "components/poker/entities/game_model_def.h"

namespace poker {

class SanityCheckTest;

/// Sanity check checks the game model after it is calculated from a new image
class SanityCheck {
 public:
  SanityCheck();

  /// Checks to see if the new_game_model makes sense, otherwise update it to
  /// make sense and increment the counter.
  /// @return false when we should throw an error and stop running when the
  /// |counter_| goes about the |kCounterthrehsold|
  bool Check(const GameModel& old_game_model, GameModel* new_game_model);
  std::string ErrorStr() const;

 private:
  friend SanityCheckTest;

  // Returns true when test passes
  bool CongruencyTest(const GameModel& new_game_model) const;

  // Returns true when test passes
  bool NewHandSanityTest(const GameModel& game_model) const;

  // Returns true when test passes
  // There should be 52 unique cards in the deck. Checks to see if each card
  // seen is unique
  bool CheckForDuplicates(const GameModel& game_model) const;

  // Called when a test fails, increments the counter by one and decides
  // whether to "debounce" the failure or signal a fault
  bool FailReturn(const GameModel& old_game_model, GameModel* new_game_model);

  // Called when all tests pass. Resets the counter and the string
  bool PassReturn();

  int counter_;
  int counter_threshold_;
  std::stringstream error_ss_;
};

}  // namespace poker

#endif  // SANITY_CHECK_H_
