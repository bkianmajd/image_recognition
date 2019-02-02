#include "components/poker/entities/comparator/comparator.h"

namespace poker {

bool operator==(Card left_card, Card right_card) {
  if (left_card.suit != right_card.suit) {
    return false;
  }
  if (left_card.value != right_card.value) {
    return false;
  }
  return true;
}

bool operator!=(Card left_card, Card right_card) {
  return !(left_card == right_card);
}

bool CheckForNewHand(const GameModel& last_game_model,
                     const GameModel& game_model) {
  // HIDDEN -> show -> HIDDEN
  // show -> show
  // HIDDEN -> Unknown -> HIDDEN
  // (rare) HIDDEN -> HIDDEN

  // Ignore this check if the player is folded
  if (game_model.player_hands[PLAYERLOC_PLAYER_ZERO].first_card.value ==
      CARD_VALUE_UNKNOWN) {
    return false;
  }

  // Ignore this check if the last game model is hidden (most likely observing)
  if (game_model.player_hands[PLAYERLOC_PLAYER_ZERO].first_card.value ==
      CARD_VALUE_HIDDEN) {
    return false;
  }

  // Check to see if the first and second card are different
  if (game_model.player_hands[PLAYERLOC_PLAYER_ZERO].first_card ==
          last_game_model.player_hands[PLAYERLOC_PLAYER_ZERO].first_card &&
      game_model.player_hands[PLAYERLOC_PLAYER_ZERO].second_card ==
          last_game_model.player_hands[PLAYERLOC_PLAYER_ZERO].second_card) {
    return false;
  }

  return true;
}

}  // namespace poker
