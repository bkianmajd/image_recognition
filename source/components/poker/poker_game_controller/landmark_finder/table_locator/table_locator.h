#ifndef TABLE_LOCATOR_H_
#define TABLE_LOCATOR_H_

#include "components/poker/entities/player_location_def.h"
#include "libraries/screenshot_creator/screenshot_creator.h"

namespace poker {

/// Returns area indications on the table such as the dealer card and the pot
/// ammount area
class TableLocator {
 public:
  explicit TableLocator(int table_size);

  template_recognition::ScreenArea GetDealerArea(
      DealerLocation dealer_location) const;
  template_recognition::ScreenArea GetPotArea() const;
  template_recognition::ScreenArea GetDealerPuck(
      PlayerLocation player_location) const;

 private:
  template_recognition::ScreenArea GetDealerPuck6() const;

  const int table_size_;
  template_recognition::ScreenshotCreator screenshot_creator_;
};

}  // namespace poker

#endif  // TABLE_LOCATOR_H_
