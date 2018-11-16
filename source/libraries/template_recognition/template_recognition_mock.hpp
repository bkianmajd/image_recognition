#ifndef TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_MOCK_
#define TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_MOCK_

#include <string>

#include "libraries/template_recognition/template_recognition_interface.h"

namespace template_recognition {

// Abstract base class that acts as the api to the recognition software.
class TemplateRecognitionMock : public TemplateRecognitionInterface {
 public:
  virtual ~TemplateRecognitionMock() {}

  // Registers an image to an image file. returns true if success.
  // returns false if image is used or image file is non-existent.
  virtual bool RegisterImage(const std::string& image) override {
    (void)image;
    return set_value_;
  }

  // Registers a template with a template id. returns true if success.
  // returns false if template id is used or image file is non-existent.
  // The template is registered in cache for faster execution at runtime
  bool RegisterTemplate(TemplateId template_id, const std::string& image) {
    (void)template_id;
    (void)image;
    return set_value_;
  }

  // Gets the point for a specific image id.
  Point GetTemplateMatch(TemplateId image_id,
                         int template_match_type) override {
    (void)image_id;
    Point point;
    point.isValid = set_value_;
  }

  bool set_value_ = true;
};

}  // namespace template_recognition

#endif  // TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_MOCK_
