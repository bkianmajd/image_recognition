#ifndef LANDMARK_FINDER_H_
#define LANDMARK_FINDER_H_

#include <memory>
#include <vector>

#include "components/image_recognition/image_recognition_api.h"
#include "components/poker/entities/card_def.h"
#include "components/poker/entities/player_location_def.h"
#include "components/poker/poker_game_controller/landmark_finder/area_finder/area_finder.h"
#include "components/poker/poker_game_controller/landmark_finder/map_to_card_converter.h"
#include "libraries/screenshot_creator/screenshot_creator.h"

namespace poker {

class LandmarkFinder {
 public:
  explicit LandmarkFinder(int number_of_chairs);

  bool UpdateBigImage(const std::vector<char>& big_image);

  Card FindLeftCard(PlayerLocation player_location);

  Card FindRightCard(PlayerLocation player_location);

  // See if there is a player occupying the chair
  ChairStatus FindChairStatus(PlayerLocation player_location);

  Card FindDealerCard(DealerLocation dealer_location);

 private:
  // Finds the card from the raw screen area (not offset by the indicator
  // location)
  Card FindCardFromRawScreenArea(template_recognition::ScreenArea& screen_area);

  // Area finder that finds the area of cards
  const std::unique_ptr<AreaFinder> area_finder_;

  // For converting from map location to card
  const MapToCardConverter map_card_converter_;

  // Screen shot that takes screenshots of an area on the screen
  template_recognition::ScreenshotCreator screenshot_creator_;

  // image recognition finders
  // This reads the indicator location, the big image of this is the screenshot
  // of the computer; The template is the indicator
  image_recognition::ImageRecognitionApi indicator_reader_;

  // The big image of this is the card map, the template is the screen area
  image_recognition::ImageRecognitionApi card_reader_;
  // image_recognition::ImageRecognitionApi chair_reader_;

  int x_indicator_location_ = 0;
  int y_indicator_location_ = 0;
};

}  // namespace poker

#endif  // LANDMARK_FINDER_H_
