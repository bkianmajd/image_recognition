#include "components/poker/entities/card_def.h"

namespace poker {

Card::Card() {
  value = CARD_VALUE_UNKNOWN;
  suit = SUIT_UNKNOWN;
}

Card::Card(CardValue arg_value, Suit arg_suit) {
  value = arg_value;
  suit = arg_suit;
}

std::ostream& operator<<(std::ostream& ss, Card card) {
  switch (card.value) {
    case 0:
      ss << "UNOWN_VALUE ";
      break;
    case 11:
      ss << "J";
      break;
    case 12:
      ss << "Q";
      break;
    case 13:
      ss << "K";
      break;
    case 14:
      ss << "HIDDEN ";
      break;
    default:
      ss << card.value;
  }

  switch (card.suit) {
    case SUIT_UNKNOWN:
      ss << "SUIT_UNKNOWN";
      break;
    case SUIT_SPADE:
      ss << "S";
      break;
    case SUIT_CLUB:
      ss << "C";
      break;
    case SUIT_DIAMOND:
      ss << "D";
      break;
    case SUIT_HEART:
      ss << "H";
      break;
    case SUIT_HIDDEN:
      ss << "HIDDEN";
      break;
  }
  return ss;
}

}  // namespace poker
