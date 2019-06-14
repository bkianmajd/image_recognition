#include "components/poker/entities/comparator/comparator.h"

namespace poker {

bool CheckForNewHand(const GameModel& last_game_model,
                     const GameModel& game_model) {
  // HIDDEN -> show -> HIDDEN
  // show -> show
  // HIDDEN -> Unknown -> HIDDEN
  // (rare) HIDDEN -> HIDDEN

  // Ignore this check if the player is folded
  if (game_model.player_hands[PLAYERLOC_PLAYER_ZERO].FirstCard().value ==
      CARD_VALUE_UNKNOWN) {
    return false;
  }

  // Ignore this check if the last game model is hidden (most likely observing)
  if (game_model.player_hands[PLAYERLOC_PLAYER_ZERO].FirstCard().value ==
      CARD_VALUE_HIDDEN) {
    return false;
  }

  // Check to see if the first and second card are different
  if (game_model.player_hands[PLAYERLOC_PLAYER_ZERO].FirstCard() ==
          last_game_model.player_hands[PLAYERLOC_PLAYER_ZERO].FirstCard() &&
      game_model.player_hands[PLAYERLOC_PLAYER_ZERO].SecondCard() ==
          last_game_model.player_hands[PLAYERLOC_PLAYER_ZERO].SecondCard()) {
    return false;
  }

  return true;
}

}  // namespace poker
