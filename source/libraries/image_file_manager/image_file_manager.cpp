#include "libraries/image_file_manager/image_file_manager.h"

namespace image_recognition {
namespace {

constexpr int kFailedToRegisterTemplateError = -1;

}  // namespace

ImageFileManager::ImageFileManager(
    const helpers::DirectoryFinder& session_directory)
    : session_directory_(session_directory) {}

bool ImageFileManager::RemoveImage(const std::string& image_name) {
  std::string abs_file = session_directory_.GetAbsPathOfTargetFile(image_name);

  auto it = stored_template_id_.find(image_name);
  if (it != stored_template_id_.end()) {
    stored_template_id_.erase(it);
  }

  return helpers::FileManager::DeleteFile(abs_file);
}

bool ImageFileManager::StoreImage(const std::string& image_name,
                                  const std::vector<char>& image_bytes) {
  std::string abs_file = session_directory_.GetAbsPathOfTargetFile(image_name);

  bool result = helpers::FileManager::StoreFile(image_bytes.data(),
                                                image_bytes.size(), abs_file);
  return result;
}

}  // namespace image_recognition
