#include "components/poker/app_finder/app_finder.h"

#include "helpers/directory_finder.h"

namespace poker {
namespace {
const std::string kSessionDirectory = "components/poker/app_finder/session";
const std::string kTemplateDirectory = "components/poker/app_finder/template";
const std::string kTemplateName = "app_landmark.jpg";

// For getting the screen area
constexpr int kXOffset = -10;
constexpr int kYOffset = -458;
constexpr int kXArea = 807;
constexpr int kYArea = 583;
}

AppFinder::AppFinder()
    : image_recongition_(
          helpers::DirectoryFinder(
              kTemplateDirectory,
              helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
          helpers::DirectoryFinder(
              kSessionDirectory,
              helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace)) {}

std::vector<char> AppFinder::Narrow(const std::vector<char>& screenshot) {
  image_recongition_.SetBigImage(screenshot);
  image_recognition::Point point =
      image_recongition_.TemplateMatch(kTemplateName);

  // The poker application was not found
  if (!point.valid) {
    return std::vector<char>();
  }

  if (!screenshot_creator_.Capture(screenshot)) {
    std::cerr << "screenshot failed to import" << std::endl;
  }

  template_recognition::ScreenArea screen_area(point.x + kXOffset, point.y + kYOffset,
                                   kXArea, kYArea);
  return screenshot_creator_.GetLastCapture(screen_area);
}

}  // namespace poker
