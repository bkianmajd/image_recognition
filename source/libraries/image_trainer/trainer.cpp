#include "libraries/image_trainer/trainer.h"

#include <iostream>

#include "helpers/file_manager/file_manager.h"

namespace image {
namespace {
constexpr int kStartFrequency = 1;
constexpr char kSplitIndicator = '_';
}  // namespace

Trainer::Trainer(helpers::DirectoryFinder session_directory)
    : session_directory_(session_directory),
      comparer_(session_directory),
      last_image_name_(0) {}

void Trainer::AddImage(const Image& image) {
  comparer_.LoadCache();
  std::string file_name = comparer_.FindImageInDirectory(image);
  if (file_name.empty()) {
    RecordWithNewFileName(image);
    return;
  }
  AddOneFrequency(image, file_name);
}

void Trainer::RecordWithNewFileName(const Image& image) {
  last_image_name_++;
  std::string file_name = CreateFileName(kStartFrequency, last_image_name_);
  helpers::FileManager::StoreFile(
      image.data(), image.size(),
      session_directory_.GetAbsPathOfTargetFile(file_name));
}

std::string Trainer::CreateFileName(int frequency, int image_name) const {
  // File name is frequency_imageName.jpg
  std::stringstream ss;
  ss << frequency << kSplitIndicator << image_name << ".jpg";
  return ss.str();
}

void Trainer::AddOneFrequency(const Image& image, const FileName& file_name) {
  // Find the new file name
  std::pair<std::string, std::string> split = SplitString(file_name);
  int frequency = ConvertStringToInt(split.first);
  frequency++;

  int image_name = ConvertStringToInt(split.second);
  std::string new_file_name = CreateFileName(frequency, image_name);

  // Delete the file
  helpers::FileManager::DeleteFile(
      session_directory_.GetAbsPathOfTargetFile(file_name));

  // Store the new file
  helpers::FileManager::StoreFile(
      image.data(), image.size(),
      session_directory_.GetAbsPathOfTargetFile(new_file_name));
}

int Trainer::ConvertStringToInt(const std::string& str) const {
  int x;
  std::stringstream ss(str);
  ss >> x;
  return x;
}

std::pair<std::string, std::string> Trainer::SplitString(
    const std::string& str) const {
  int index = static_cast<int>(str.find(kSplitIndicator));
  if (index == -1 || index == 0) {
    std::cerr << "unable to find the split indicator" << std::endl;
    assert(false);
  }
  // taking out the . jpg
  if (str.size() < 4) {
    std::cerr << "invalid string " << str << std::endl;
    assert(false);
  }

  return std::make_pair(std::string(str.begin(), str.begin() + index),
                        std::string(str.begin() + index + 1, str.end() - 4));
}

}  // namespace image
