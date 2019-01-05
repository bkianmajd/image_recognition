#ifndef TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_MOCK_
#define TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_MOCK_

#include <string>

#include "libraries/image_recognition/template_recognition/template_recognition_interface.h"

namespace recognition {

// Abstract base class that acts as the api to the recognition software.
class TemplateRecognitionMock : public TemplateRecognitionInterface {
 public:
  ~TemplateRecognitionMock() override {}

  // Registers an image to an image file. returns true if success.
  // returns false if image is used or image file is non-existent.
  bool RegisterImage(const image::Image& image) override {
    (void)image;
    return set_value_;
  }

  // Registers a template with a template id. returns true if success.
  // returns false if template id is used or image file is non-existent.
  // The template is registered in cache for faster execution at runtime
  bool RegisterTemplate(TemplateId template_id,
                        const image::Image& image) override {
    (void)image;
    (void)template_id;
    return set_value_;
  }

  // Gets the point for a specific image id.
  std::vector<ProbabilityPoint> GetTemplateMatch(TemplateId image_id) override {
    (void)image_id;
    ProbabilityPoint point;
    point.isValid = set_value_;
    std::vector<ProbabilityPoint> points;
    points.push_back(point);
    return points;
  }

  bool set_value_ = true;
};

}  // namespace recognition

#endif  // TEMPLATE_RECOGNITION_TEMPLATE_RECOGNITION_MOCK_
