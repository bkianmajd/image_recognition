#include "components/poker/poker_game_controller/landmark_finder/card_reader/card_reader.h"

#include "components/poker/poker_game_controller/landmark_finder/map_images/value_comparer/value_comparer.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager/file_manager.h"

namespace poker {
namespace {
// The spacing of the maps
constexpr int kGridLine = 30;

constexpr int kDefaultWidth = 16;
constexpr int kDefaultHeight = 17;
const template_recognition::ScreenArea kValueArea(1, 3, kDefaultWidth,
                                                  kDefaultHeight);
const template_recognition::ScreenArea kSuitArea(1, 2 + kDefaultHeight,
                                                 kDefaultWidth, kDefaultHeight);
const std::string kTemplateName = "template.jpg";

const std::string kTemplateDirectory =
    "components/poker/poker_game_controller/landmark_finder/map_images";
const std::string kValueDirectory =
    "components/poker/poker_game_controller/landmark_finder/map_images/"
    "value_comparer";

const std::string kSuitMap = "suit_map.jpg";

}  // namespace

CardReader::CardReader()
    : template_directory_(
          helpers::CreateDirectoryFinderFromWorkspace(kTemplateDirectory)),
      suit_recognition_(
          helpers::CreateDirectoryFinderFromWorkspace(kTemplateDirectory)),
      value_comparer_(
          helpers::CreateDirectoryFinderFromWorkspace(kValueDirectory)) {
  std::vector<char> big_image_bytes = helpers::FileManager::ReadFile(
      template_directory_.GetAbsPathOfTargetFile(kSuitMap));
  // TODO() : Assert vector size here
  suit_recognition_.SetBigImage(big_image_bytes);

  pipeline_.AddToPipeline(image::PipelineType::NOISE_REDUCTION);
  pipeline_.AddToPipeline(image::PipelineType::TOP_LEFT_ALIGNMENT);
  value_comparer_.LoadCache();
}

Card CardReader::ConvertToCard(const std::vector<char>& card_bytes) {
  screenshot_creator_.Capture(card_bytes);
  value_ = screenshot_creator_.GetLastCapture(kValueArea);
  suit_ = screenshot_creator_.GetLastCapture(kSuitArea);

  Card card;
  card.suit = FindSuit();
  card.value = FindValue();

  // Only the suit picks up hidden values
  if (card.suit == SUIT_HIDDEN) {
    card.value = CARD_VALUE_HIDDEN;
  }

  return card;
}

Suit CardReader::FindSuit() {
  suit_recognition_.AddTemplateImage(suit_, kTemplateName);
  recognition::Point point = suit_recognition_.TemplateMatch(kTemplateName);
  if (!point.valid) {
    return SUIT_UNKNOWN;
  }

  int map_area = kGridLine;
  for (int suit = SUIT_SPADE; suit <= SUIT_HIDDEN; ++suit) {
    if (point.x < map_area) {
      return static_cast<Suit>(suit);
    }
    map_area += kGridLine;
  }

  // After the SUIT_HIDDEN is another SUIT_HIDDEN value
  return SUIT_HIDDEN;
}
CardValue CardReader::FindValue() {
  // Apply value to pipeline
  std::vector<image::Image> images = pipeline_.Run(value_);
  assert(images.size() == 1);
  image::Image& reduced_image = images[0];

  // For debugging
  // helpers::FileManager::StoreFile(
  //    reduced_image.data(), reduced_image.size(),
  //    template_directory_.GetAbsPathOfTargetFile("output_test.jpg"));

  // compare the reduced image
  std::string image_name = value_comparer_.FindImageInDirectory(reduced_image);
  return Convert(image_name);
}

}  // namespace poker
