#include "components/poker/poker_game_controller/landmark_finder/landmark_finder.h"

#include <cassert>

#include "helpers/file_manager/file_manager.h"
#include "helpers/memory_helper.hpp"

namespace poker {
namespace {

}  // namespace

LandmarkFinder::LandmarkFinder(int table_size)
    : table_locator_(std::make_unique<TableLocator>(table_size)) {
  for (int i = 0; i < table_size; ++i) {
    player_locators_.push_back(
        PlayerLocator(table_size, static_cast<PlayerLocation>(i)));
  }
}

bool LandmarkFinder::UpdateBigImage(const std::vector<char>& big_image) {
  // Set the screenshot to capture the big image
  if (!screenshot_creator_.Capture(big_image)) {
    return false;
  }

  return true;
}

Card LandmarkFinder::FindLeftCard(PlayerLocation player_location) {
  template_recognition::ScreenArea screen_area =
      player_locators_.at(static_cast<size_t>(player_location))
          .GetLeftCardArea();

  return FindCardFromRawScreenArea(screen_area);
}

Card LandmarkFinder::FindRightCard(PlayerLocation player_location) {
  template_recognition::ScreenArea screen_area =
      player_locators_.at(static_cast<size_t>(player_location))
          .GetRightCardArea();
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
      table_locator_->GetDealerArea(dealer_location);
  return FindCardFromRawScreenArea(screen_area);
}

Card LandmarkFinder::FindCardFromRawScreenArea(
    template_recognition::ScreenArea& screen_area) {
  Card card;
  std::vector<char> card_raw_bytes =
      screenshot_creator_.GetLastCapture(screen_area);

  if (card_raw_bytes.size() == 0) {
    std::cerr << "Landmark finder: Failed to capture screenshot" << std::endl;
    return card;
  }

  return card_reader_.ConvertToCard(card_raw_bytes);
}

}  // namespace poker
