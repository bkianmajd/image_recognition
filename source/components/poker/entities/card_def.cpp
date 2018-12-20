#include "components/poker/entities/card_def.h"

namespace poker {

std::ostream& operator<<(std::ostream& ss, Card card) {
  switch (card.card_value) {
    case 0:
      ss << "UNOWN_VALUE ";
      break;
    case 11:
      ss << "J ";
      break;
    case 12:
      ss << "Q ";
      break;
    case 13:
      ss << "K ";
      break;
    default:
      ss << card.card_value << " ";
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
  }
  return ss;
}

}  // namespace poker
