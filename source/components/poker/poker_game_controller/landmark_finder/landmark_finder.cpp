#include "components/poker/poker_game_controller/landmark_finder/landmark_finder.h"

#include <cassert>

#include "components/poker/poker_game_controller/landmark_finder/area_finder/six_player_area_finder.h"
#include "helpers/file_manager/file_manager.h"
#include "helpers/memory_helper.hpp"

namespace poker {
namespace {
const std::string kMapImageDirectory =
    "components/poker/poker_game_controller/landmark_finder/map_images";

const std::string kSessionDirectory =
    "components/poker/poker_game_controller/landmark_finder/session_directory";

const std::string kCardMap = "card_map.jpg";

const std::string kTemplateImageName = "template_image.jpg";

constexpr helpers::DirectoryFinder::ReferenceFrame kRelativePath =
    helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace;

std::unique_ptr<AreaFinder> MakeAreaFinder(int number_of_chairs) {
  switch (number_of_chairs) {
    case 6:
      return std::make_unique<SixPlayerAreaFinder>();
      break;
    default:
      std::cerr << "do not have table data for area finder" << std::endl;
      assert(false);
  }
  return nullptr;
}

}  // namespace

LandmarkFinder::LandmarkFinder(int number_of_chairs)
    : area_finder_(MakeAreaFinder(number_of_chairs)),
      map_card_converter_(),
      indicator_reader_(
          helpers::DirectoryFinder(kMapImageDirectory, kRelativePath),
          helpers::DirectoryFinder(kSessionDirectory, kRelativePath)),
      card_reader_(helpers::DirectoryFinder(kMapImageDirectory, kRelativePath),
                   helpers::DirectoryFinder(kSessionDirectory, kRelativePath)) {
  helpers::DirectoryFinder map_directory(kMapImageDirectory, kRelativePath);
  std::vector<char> map_image = helpers::FileManager::ReadFile(
      map_directory.GetAbsPathOfTargetFile(kCardMap));

  // Sets the card readers big image to the card_map
  assert(map_image.size() > 0);
  assert(card_reader_.SetBigImage(map_image));
}

bool LandmarkFinder::UpdateBigImage(const std::vector<char>& big_image) {
  // Set the screenshot to capture the big image
  if (!screenshot_creator_.Capture(big_image)) {
    return false;
  }

  // Set the landmark finder to update its big image
  if (!indicator_reader_.SetBigImage(big_image)) {
    return false;
  }

  // need to find the indicator??

  return true;
}

Card LandmarkFinder::FindLeftCard(PlayerLocation player_location) {
  template_recognition::ScreenArea screen_area =
      area_finder_->GetCardAreaLeft(player_location);
  return FindCardFromRawScreenArea(screen_area);
}

Card LandmarkFinder::FindRightCard(PlayerLocation player_location) {
  template_recognition::ScreenArea screen_area =
      area_finder_->GetCardAreaRight(player_location);
  return FindCardFromRawScreenArea(screen_area);
}

// See if there is a player occupying the chair
ChairStatus LandmarkFinder::FindChairStatus(PlayerLocation player_location) {
  // TODO(BK) Finish this
  (void)player_location;
  return ChairStatus::CHAIR_STATUS_OCCUPIED;
}

Card LandmarkFinder::FindDealerCard(DealerLocation dealer_location) {
  template_recognition::ScreenArea screen_area =
      area_finder_->GetDealerCard(dealer_location);
  return FindCardFromRawScreenArea(screen_area);
}

Card LandmarkFinder::FindCardFromRawScreenArea(
    template_recognition::ScreenArea& screen_area) {
  Card card;
  // Find a subset of the big image
  screen_area.x += x_indicator_location_;
  screen_area.y += y_indicator_location_;
  std::vector<char> raw_bytes = screenshot_creator_.GetLastCapture(screen_area);

  if (raw_bytes.size() == 0) {
    std::cerr << "Landmark finder: Failed to capture screenshot" << std::endl;
    return card;
  }

  card_reader_.AddTemplateImage(raw_bytes, kTemplateImageName);
  image_recognition::Point point =
      card_reader_.TemplateMatch(kTemplateImageName);
  if (!point.valid) {
    return card;
  }

  return map_card_converter_.Convert(point.x, point.y);
}

}  // namespace poker
