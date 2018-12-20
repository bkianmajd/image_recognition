#include "components/poker/model_generator/model_generator.h"

#include "components/poker/entities/player_location_def.h"

namespace poker {

ModelGenerator::ModelGenerator() {}

void ModelGenerator::SetFlop(Card first_card, Card second_card,
                             Card third_card) {
  game_model_.dealer_cards[DEALER_ONE] = first_card;
  game_model_.dealer_cards[DEALER_TWO] = second_card;
  game_model_.dealer_cards[DEALER_THREE] = third_card;
}

void ModelGenerator::SetTurn(Card card) {
  game_model_.dealer_cards[DEALER_FOUR] = card;
}

void ModelGenerator::SetRiver(Card card) {
  game_model_.dealer_cards[DEALER_FIVE] = card;
}

void ModelGenerator::PlayerDeal(Card first_card, Card second_card) {
  game_model_.player_cards[PLAYERLOC_PLAYER_ZERO].left_card = first_card;
  game_model_.player_cards[PLAYERLOC_PLAYER_ZERO].left_card = second_card;
}

void ModelGenerator::Reset() {
  game_model_.game_status.player_status[PLAYERLOC_PLAYER_ZERO] = PLAYER_STATUS_UNKNOWN;

}

}  // namespace poker
