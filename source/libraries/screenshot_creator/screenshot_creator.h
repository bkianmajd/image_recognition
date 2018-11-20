#ifndef SCREENSHOT_CREATOR_H_
#define SCREENSHOT_CREATOR_H_

#include <iostream>
#include <vector>

#include <QApplication>
#include <QDesktopWidget>
#include <QPixmap>
#include <QWidget>
#include <QtWidgets>

namespace template_recognition {

class ScreenshotCreator : QWidget {
 public:
  ScreenshotCreator();

  bool Capture();

  bool Capture(int x, int y, int width, int height);

  bool SaveLastCaptureToFile(const std::string& abs_path);

  std::vector<char> GetLastCapture();

 private:
  QScreen* GetScreen();

  QPixmap original_pixmap_;
  QDataStream data_stream_;
};

}  // namespace template_recognition

#endif  // SCREENSHOT_CREATOR_H_
