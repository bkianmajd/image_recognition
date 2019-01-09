#ifndef VALUE_COMPARER_H_
#define VALUE_COMPARER_H_

#include <memory>
#include <string>
#include <vector>

#include "components/poker/entities/card_def.h"

namespace poker {

CardValue Convert(const std::string& file_name);

}  // namespace poker

#endif  // VALUE_COMPARER_H_
