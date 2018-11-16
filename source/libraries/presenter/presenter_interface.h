#ifndef TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_INTERFACE_
#define TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_INTERFACE_

#include <string>

namespace template_recognition {

// Abstract base class that acts as the api to the recognition software.
class PresenterInterface {
 public:
  virtual ~PresenterInterface() {}

  // Registers an image to an image file. returns true if success.
  // returns false if image is used or image file is non-existent.
  virtual bool SetModel(const std::string& image) = 0;

  // Registers a template with a template id. returns true if success.
  // returns false if template id is used or image file is non-existent.
  // The template is registered in cache for faster execution at runtime
    virtual bool PresentModel(TemplateId template_id,
                                const std::string& image) = 0;

};

}  // namespace template_recognition

#endif  // TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_INTERFACE_
