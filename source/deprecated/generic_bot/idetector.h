#ifndef BOT_IDETECTOR_H_
#define BOT_IDETECTOR_H_

#include <vector>

#include "helpers/directory_finder.h"

namespace bot {

// Abstract base class to detect images
template <typename DetectorType>
class IDetector {
 public:
  virtual ~IDetector() = default;

  // Registers a set of template images
  virtual bool RegisterTemplateImages(
      const helpers::DirectoryFinder& directory_finder) = 0;

  // Updates a vector of a Detector type struct (i.e. list of detected objects)
  virtual void Update(const std::string& big_image_name,
                      std::vector<DetectorType>* detected_types) = 0;
};

}  // namespace bot

#endif  // BOT_IDETECTOR_H_
