#ifndef MAP_TO_CARD_CONVERTER_H_
#define MAP_TO_CARD_CONVERTER_H_

#include "components/poker/entities/card_def.h"

namespace poker {

// Converts a point to the card definition
class MapToCardConverter {
 public:
  Card Convert(int x_location, int y_location) const;
};

}  // namespace poker

#endif  // MAP_TO_CARD_CONVERTER_H_
