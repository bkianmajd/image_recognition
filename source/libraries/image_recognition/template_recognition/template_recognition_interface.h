#ifndef TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_INTERFACE_
#define TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_INTERFACE_

#include <string>
#include <vector>
#include "libraries/image_recognition/template_recognition/template_recognition_defs.h"

namespace template_recognition {

// Abstract base class that acts as the api to the recognition software.
class TemplateRecognitionInterface {
 public:
  virtual ~TemplateRecognitionInterface() {}

  // Registers an image to an image file. returns true if success.
  // returns false if image is used or image file is non-existent.
  virtual bool RegisterImage(const std::string& image) = 0;

  // Registers a template with a template id. returns true if success.
  // returns false if template id is used or image file is non-existent.
  // The template is registered in cache for faster execution at runtime
  virtual bool RegisterTemplate(TemplateId template_id,
                                const std::string& image) = 0;

  virtual bool RegisterTemplate(TemplateId template_id,
                                const std::vector<char>& bytes) = 0;

  // Gets the point for a specific image id WRT the registered image.
  virtual std::vector<Point> GetTemplateMatch(TemplateId image_id) = 0;
};

}  // namespace template_recognition

#endif  // TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_INTERFACE_
