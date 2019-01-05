#include "components/poker/poker_game_controller/poker_landmark_generator/poker_landmark_generator.h"

#include <cassert>

#include "helpers/file_manager/file_manager.h"
#include "libraries/screenshot_creator/screenshot_creator.h"

namespace poker {
namespace {
const std::string kTemplateDirectory =
    "components/poker/poker_game_controller/poker_landmark_generator/"
    "template_directory";

const std::string kSessionDirectory =
    "components/poker/poker_game_controller/poker_landmark_generator/"
    "landmark_session_directory";

const std::string kBigImageName = "map.jpg";

const std::string kTemplateImageName = "template_image.jpg";

constexpr helpers::DirectoryFinder::ReferenceFrame kRelativePath =
    helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace;

}  // namespace

PokerLandmarkGenerator::PokerLandmarkGenerator(
    const LandmarkRequestDataArray& landmark_request_data_array)
    : landmark_request_data_array_(landmark_request_data_array),
      image_recognition_api_(
          helpers::DirectoryFinder(kTemplateDirectory, kRelativePath),
          helpers::DirectoryFinder(kSessionDirectory, kRelativePath)) {
  // Load the map into the image_recognition_api
  helpers::DirectoryFinder directory_finder(kTemplateDirectory, kRelativePath);
  std::vector<char> map_image = helpers::FileManager::ReadFile(
      directory_finder.GetAbsPathOfTargetFile(kBigImageName));
  assert(map_image.size() > 0);
  assert(image_recognition_api_.SetBigImage(map_image));
}

recognition::Point PokerLandmarkGenerator::ConvertToPoint(
    const template_recognition::ScreenArea& screen_area, int x_indicator,
    int y_indicator) {
  recognition::Point return_point;
  return_point.valid = false;

  template_recognition::ScreenArea global_screen_area(
      screen_area.x + x_indicator, screen_area.y + y_indicator,
      screen_area.width, screen_area.height);

  std::vector<char> template_image =
      screenshot_creator_.GetLastCapture(global_screen_area);
  if (template_image.size() == 0) {
    std::cerr << "failed to get raw data from screenshot" << std::endl;
    return return_point;
  }

  if (!image_recognition_api_.AddTemplateImage(template_image,
                                               kTemplateImageName)) {
    std::cerr << "failed to add template image" << std::endl;
    return return_point;
  }

  return image_recognition_api_.TemplateMatch(kTemplateImageName);
}

LandmarkResponseDataArray PokerLandmarkGenerator::GenerateRelativeToIndicator(
    const std::vector<char>& screenshot, int x_indicator, int y_indicator) {
  LandmarkResponseDataArray landmark_response_data_array;

  // Capture a subset of the screenshot to a template image
  if (!screenshot_creator_.Capture(screenshot)) {
    std::cerr << "failed to capture screenshot" << std::endl;
    return landmark_response_data_array;
  }

  // The landmark generator creates a template image at a spot its expecting the
  // image. If its found, it returns true;
  for (int i = 0; i < LANDMARK_SIZE; ++i) {
    const LandmarkRequestData& landmark_request_data =
        landmark_request_data_array_[i];

    if (landmark_request_data.is_search == false) {
      continue;
    }

    // find the template image and store it in the response
    landmark_response_data_array[i].left_card = ConvertToPoint(
        landmark_request_data.left_card, x_indicator, y_indicator);

    landmark_response_data_array[i].right_card = ConvertToPoint(
        landmark_request_data.right_card, x_indicator, y_indicator);
  }

  return landmark_response_data_array;
}

}  // namespace poker
