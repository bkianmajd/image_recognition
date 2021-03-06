#ifndef TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_INTERFACE_
#define TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_INTERFACE_

#include <string>
#include <vector>

#include "libraries/image_def/image_def.h"
#include "libraries/image_recognition/template_recognition/template_recognition_defs.h"

namespace recognition {

// Abstract base class that acts as the api to the recognition software.
class TemplateRecognitionInterface {
 public:
  virtual ~TemplateRecognitionInterface() = default;

  // Registers an image to an image file. returns true if success.
  // returns false if image is used or image file is non-existent.
  virtual bool RegisterImage(const image::Image& image) = 0;

  // Registers a template with a template id. returns true if success.
  // returns false if template id is used or image file is non-existent.
  // The template is registered in cache for faster execution at runtime
  virtual bool RegisterTemplate(TemplateId template_id,
                                const image::Image& image) = 0;

  // Gets the point for a specific image id WRT the registered image.
  virtual std::vector<ProbabilityPoint> GetTemplateMatch(
      TemplateId image_id) = 0;
};

}  // namespace recognition

#endif  // TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_INTERFACE_
