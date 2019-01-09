#include "components/poker/poker_game_controller/landmark_finder/map_images/value_comparer/value_comparer.h"

#include <iostream>
#include <sstream>

namespace poker {
namespace {
constexpr char kSeperator = '-';
}

CardValue Convert(const std::string& file_name) {
  CardValue value;
  value = CARD_VALUE_UNKNOWN;
  size_t index = file_name.find_first_of(kSeperator);
  // index not found
  if (index == std::string::npos) {
    return value;
  }

  std::string card_name(file_name.begin() + 1,
                        file_name.begin() + static_cast<int>(index));
  std::stringstream ss;
  for (char a : card_name) {
    if (!std::isdigit(a)) {
      // error in parsing
      std::cerr << "file name is not a digit" << std::endl;
      return value;
    }
    ss << a;
  }
  int number;
  ss >> number;

  if (number < 0 || number > 13) {
    std::cerr << "number range is invalid" << std::endl;
    return value;
  }

  value = static_cast<CardValue>(number);
  return value;
}

}  // namespace poker
