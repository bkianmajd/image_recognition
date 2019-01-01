#include "components/poker/poker_game_controller/landmark_finder/card_reader/card_reader.h"

#include "helpers/file_manager/file_manager.h"

namespace poker {
namespace {
// The spacing of the maps
constexpr int kGridLine = 50;

constexpr int kDefaultWidth = 16;
constexpr int kDefaultHeight = 17;
const template_recognition::ScreenArea kValueArea(1, 3, kDefaultWidth,
                                                  kDefaultHeight);
const template_recognition::ScreenArea kSuitArea(1, 2 + kDefaultHeight,
                                                 kDefaultWidth, kDefaultHeight);
const std::string kTemplateName = "template.jpg";

const std::string kTemplateDirectory =
    "components/poker/poker_game_controller/landmark_finder/card_reader/"
    "template_directory";
const std::string kSessionDirectory =
    "components/poker/poker_game_controller/landmark_finder/card_reader/"
    "session_directory";

const std::string kSuitMap = "suit_map.jpg";
const std::string kValueMap = "value_map.jpg";

}  // namespace

CardReader::CardReader()
    : template_directory_(
          helpers::CreateDirectoryFinderFromWorkspace(kTemplateDirectory)),
      suit_recognition_(
          helpers::CreateDirectoryFinderFromWorkspace(kTemplateDirectory),
          helpers::CreateDirectoryFinderFromWorkspace(kSessionDirectory)),
      value_recognition_(
          helpers::CreateDirectoryFinderFromWorkspace(kTemplateDirectory),
          helpers::CreateDirectoryFinderFromWorkspace(kSessionDirectory)) {
  std::vector<char> big_image_bytes = helpers::FileManager::ReadFile(
      template_directory_.GetAbsPathOfTargetFile(kSuitMap));
  // TODO() : Assert vector size here
  suit_recognition_.SetBigImage(big_image_bytes);

  big_image_bytes = helpers::FileManager::ReadFile(
      template_directory_.GetAbsPathOfTargetFile(kValueMap));
  // TODO() : Assert vector size here
  value_recognition_.SetBigImage(big_image_bytes);
}

Card CardReader::ConvertToCard(const std::vector<char>& card_bytes) {
  screenshot_creator_.Capture(card_bytes);
  value_ = screenshot_creator_.GetLastCapture(kValueArea);
  suit_ = screenshot_creator_.GetLastCapture(kSuitArea);

  Card card;
  card.suit = FindSuit();
  card.value = FindValue();
  return card;
}

Suit CardReader::FindSuit() {
  suit_recognition_.AddTemplateImage(suit_, kTemplateName);
  image_recognition::Point point =
      suit_recognition_.TemplateMatch(kTemplateName);
  if (!point.valid) {
    return SUIT_UNKNOWN;
  }

  int map_area = kGridLine;
  for (int suit = SUIT_SPADE; suit <= SUIT_HEART; ++suit) {
    if (point.x < map_area) {
      return static_cast<Suit>(suit);
    }
    map_area += kGridLine;
  }

  // Techncially should not be reached
  // assert(false);
  return SUIT_UNKNOWN;
}
CardValue CardReader::FindValue() {
  suit_recognition_.AddTemplateImage(suit_, kTemplateName);
  // Get the pixel location
  image_recognition::Point point =
      suit_recognition_.TemplateMatch(kTemplateName);
  // Ignore the pixel if its not valid
  if (!point.valid) {
    return CARD_VALUE_UNKNOWN;
  }

  // Checking each grid box
  int map_area = kGridLine;
  for (int value = CARD_VALUE_ACE; value <= CARD_VALUE_KING; ++value) {
    if (point.x < map_area) {
      return static_cast<CardValue>(value);
    }
    map_area += kGridLine;
  }

  // Techncially should not be reached
  assert(false);
  return CARD_VALUE_UNKNOWN;
}

}  // namespace poker