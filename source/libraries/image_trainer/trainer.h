#ifndef TRAINER_H_
#define TRAINER_H_

#include <unordered_map>

#include "gtest/gtest_prod.h"
#include "helpers/directory_finder.h"
#include "libraries/image_comparer/comparer.h"
#include "libraries/image_def/image_def.h"

namespace image {

/// Record images if new to the name 'frequency_imagename.jpg'
class Trainer {
 public:
  explicit Trainer(helpers::DirectoryFinder session_directory);

  /// Returns true if the image was already recognized
  /// False if the image was new
  bool AddImage(const Image& image);

 private:
  FRIEND_TEST(TrainerTest, SplitTest);
  FRIEND_TEST(TrainerTest, CreateFileNameTest);
  FRIEND_TEST(TrainerTest, ConvertStringToIntTest);

  using FileName = std::string;
  using Frequency = int;

  void RecordWithNewFileName(const Image& image);
  void AddOneFrequency(const Image& image, const FileName& file_name);

  int ConvertStringToInt(const std::string& str) const;
  std::string CreateFileName(int image_name, int frequency) const;
  std::string CreateFileName(const std::string& image_name, int frequency) const;
  std::pair<std::string, std::string> SplitString(const std::string& str) const;

  const helpers::DirectoryFinder session_directory_;
  Comparer comparer_;
  int last_image_name_;
};

}  // namespace image

#endif  // TRAINER_H_
