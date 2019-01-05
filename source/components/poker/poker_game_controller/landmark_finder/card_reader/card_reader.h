#ifndef CARD_READER_H_
#define CARD_READER_H_

#include <vector>

#include "libraries/image_recognition/image_recognition_api.h"
#include "components/poker/entities/card_def.h"
#include "gtest/gtest_prod.h"
#include "helpers/directory_finder.h"
#include "libraries/screenshot_creator/screenshot_creator.h"

namespace poker {
class CardReaderTest;

class CardReader {
 public:
  CardReader();

  Card ConvertToCard(const std::vector<char>& card_bytes);

 private:
  friend CardReaderTest;
  FRIEND_TEST(CardReaderTest, AreaTest);
  void SplitImage();
  Suit FindSuit();
  CardValue FindValue();

  helpers::DirectoryFinder template_directory_;
  template_recognition::ScreenshotCreator screenshot_creator_;
  image_recognition::ImageRecognitionApi suit_recognition_;
  image_recognition::ImageRecognitionApi value_recognition_;
  std::vector<char> value_;
  std::vector<char> suit_;
};

}  // namespace poker

#endif  // CARD_READER_H_
