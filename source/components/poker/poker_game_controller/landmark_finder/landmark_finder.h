#ifndef LANDMARK_FINDER_H_
#define LANDMARK_FINDER_H_

#include <memory>
#include <vector>

#include "components/poker/entities/card_def.h"
#include "components/poker/entities/player_location_def.h"
#include "components/poker/poker_game_controller/landmark_finder/card_reader/card_reader.h"
#include "components/poker/poker_game_controller/landmark_finder/player_locator/player_locator.h"
#include "components/poker/poker_game_controller/landmark_finder/table_locator/table_locator.h"
#include "libraries/image_recognition/image_recognition_api.h"
#include "libraries/screenshot_creator/screenshot_creator.h"

namespace poker {

class LandmarkFinder {
 public:
  explicit LandmarkFinder(int table_size);

  bool UpdateBigImage(const std::vector<char>& big_image);

  Card FindLeftCard(PlayerLocation player_location);

  Card FindRightCard(PlayerLocation player_location);

  /// See if there is a player occupying the chair
  ChairStatus FindChairStatus(PlayerLocation player_location);

  Card FindDealerCard(DealerLocation dealer_location);

  /// Checks to see if there is a decision to be made
  bool FindDecisionEvent() const;

 private:
  // Area finder for finding the card of the dealer location
  const std::unique_ptr<TableLocator> table_locator_;

  // Area finder that finds the area of cards
  // For converting from map location to card
  const std::vector<PlayerLocator> player_locators_;

  // Finds the card from the raw screen area (not offset by the indicator
  // location)
  Card FindCardFromRawScreenArea(template_recognition::ScreenArea& screen_area);

  // For converting image to card
  CardReader card_reader_;

  // Screen shot that takes screenshots of an area on the screen
  template_recognition::ScreenshotCreator screenshot_creator_;

  // For checking a decision event
  // recognition::ImageRecognitionApi decision_event_searcher_;
};

}  // namespace poker

#endif  // LANDMARK_FINDER_H_
