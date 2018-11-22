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

  bool SaveLastCaptureToFile(const std::string& abs_path);

  bool CaptureFromBigImage(const std::vector<char>& big_image,
                           const ScreenArea& screen_area);

  std::vector<char> GetLastCapture();

 private:
  QScreen* GetScreen();

  QPixmap original_pixmap_;
  QDataStream data_stream_;
};

}  // namespace template_recognition

#endif  // SCREENSHOT_CREATOR_H_
