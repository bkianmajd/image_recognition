#include "libraries/screenshot_creator/screenshot_creator.h"

namespace template_recognition {
namespace {

constexpr WId kWindowId = 0;

}  // namespace

ScreenshotCreator::ScreenshotCreator() {}

QScreen* ScreenshotCreator::GetScreen() {
  QScreen* screen = QGuiApplication::primaryScreen();
  const QWindow* window = windowHandle();
  if (window) {
    screen = window->screen();
  }

  return screen;
}

bool ScreenshotCreator::Capture() {
  QScreen* screen = GetScreen();
  if (screen == nullptr) {
    return false;
  }

  original_pixmap_ = screen->grabWindow(0);
  return true;
}

bool ScreenshotCreator::Capture(const ScreenArea& screen_area) {
  QScreen* screen = GetScreen();
  if (screen == nullptr) {
    return false;
  }
  original_pixmap_ = screen->grabWindow(kWindowId, screen_area.x, screen_area.y,
                                        screen_area.width, screen_area.height);

  return true;
}

bool ScreenshotCreator::SaveLastCaptureToFile(
    const std::string& abs_file_path) {
  if (!original_pixmap_.save(abs_file_path.c_str())) {
    std::cerr << "Could not save" << abs_file_path << std::endl;
    return false;
  }

  return true;
}

std::vector<char> ScreenshotCreator::GetLastCapture() {
  // Preparation of our QPixmap
  QByteArray bArray;
  QBuffer buffer(&bArray);
  buffer.open(QIODevice::WriteOnly);
  original_pixmap_.save(&buffer, "JPG");

  std::vector<char> return_vector(bArray.begin(), bArray.end());
  return return_vector;
}

bool ScreenshotCreator::CaptureFromBigImage(const std::vector<char>& big_image,
                                            const ScreenArea& screen_area) {
  if (!original_pixmap_.loadFromData((const uchar*)(big_image.data()),
                                     big_image.size(), "JPG")) {
    std::cerr << "failed to load from data" << std::endl;
    return false;
  }

  original_pixmap_ = original_pixmap_.copy(
      screen_area.x, screen_area.y, screen_area.width, screen_area.height);
  return true;
}

}  // namespace template_recognition
