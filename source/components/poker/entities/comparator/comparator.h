#ifndef ENTITIES_COMPARATOR_H_
#define ENTITIES_COMPARATOR_H_

#include "components/poker/entities/card_def.h"
#include "components/poker/entities/game_model_def.h"

/// @brief Contains comparison functions
namespace poker {

bool operator==(Card left_card, Card right_card);
bool operator!=(Card left_card, Card right_card);

bool CheckForNewHand(const GameModel& last_game_model,
                     const GameModel& game_model);

}  // namespace poker

#endif  // ENTITIES_COMPARATOR_H_
