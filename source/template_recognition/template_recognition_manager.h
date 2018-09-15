#ifndef TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_MANAGER_
#define TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_MANAGER_

#include <string>
#include <unordered_map>

#include "gtest/gtest_prod.h"
#include "helpers/directory_finder.h"
#include "helpers/file_manager/file_manager.h"
#include "template_recognition/template_recognition_defs.h"
#include "template_recognition/template_recognition_interface.h"

namespace template_recognition {

/// Class that acts as the API to the template recognition component
class TemplateRecognitionManager {
 public:
  TemplateRecognitionManager(
      helpers::DirectoryFinder* session_directory,
      helpers::FileManager* file_manager,
      template_recognition::TemplateRecognitionInterface* template_recognition);

  bool StoreImage(const std::string& image_name,
                  const std::vector<char>& image_bytes);

  bool TemplateMatch(const std::string& big_image_name,
                     const std::string& template_image_name,
                     Point* response_point);

 private:
  int GetTemplateIdOrRegisterTemplate(const std::string& image_name);

  // The data directory is where all the images are currently stored
  helpers::DirectoryFinder* data_directory_;

  // The file manager wraps certain function calls. All inputs are abs path.
  helpers::FileManager* file_manager_;

  // TemplateRecognitionInterface
  template_recognition::TemplateRecognitionInterface* template_recognition_;

  // The map key is the filename, the map value is the stored templateId
  std::unordered_map<std::string, template_recognition::TemplateId>
      stored_template_id_;
};

}  // namespace template_recognition

#endif  // TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_MANAGER_
