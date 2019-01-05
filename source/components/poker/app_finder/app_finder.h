#ifndef APP_FINDER_H_
#define APP_FINDER_H_

#include <vector>

#include "libraries/image_recognition/image_recognition_api.h"
#include "libraries/screenshot_creator/screenshot_creator.h"

namespace poker {

class AppFinder {
 public:
  AppFinder();

  std::vector<char> Narrow(const std::vector<char>& screenshot);

 private:
  // For finding landmarks of the application
  recognition::ImageRecognitionApi image_recongition_;

  // For taking a screenshot of the subset
  template_recognition::ScreenshotCreator screenshot_creator_;
};

}  // namespace app_finder

#endif  // poker
