#ifndef SCREENSHOT_CREATOR_H_
#define SCREENSHOT_CREATOR_H_

#include <iostream>
#include <vector>

// #include <QApplication>
// #include <QDesktopWidget>
#include <QPixmap>
#include <QWidget>
#include <QtWidgets>

namespace template_recognition {

struct ScreenArea {
  ScreenArea() : x(0), y(0), width(0), height(0) {}

  ScreenArea(int p_x, int p_y, int p_width, int p_height)
      : x(p_x), y(p_y), width(p_width), height(p_height) {}

  int x;
  int y;
  int width;
  int height;
};

class ScreenshotCreator : QWidget {
 public:
  ScreenshotCreator();

  bool Capture();

  bool Capture(const ScreenArea& screen_area);

  // Captures a raw data image instead of taking a screenshot
  bool Capture(const std::vector<char>& big_image);

  bool SaveLastCaptureToFile(const std::string& abs_path);

  std::vector<char> GetLastCapture();

  // Gets a subset of the last capture
  std::vector<char> GetLastCapture(const ScreenArea& screen_area);

 private:
  QScreen* GetScreen();

  QPixmap original_pixmap_;
};

}  // namespace template_recognition

#endif  // SCREENSHOT_CREATOR_H_
