#ifndef SIX_PLAYER_AREA_FINDER_H_
#define SIX_PLAYER_AREA_FINDER_H_

#include "components/poker/poker_game_controller/landmark_finder/area_finder/area_finder.h"

namespace poker {

class SixPlayerAreaFinder final : public AreaFinder {
public:
public:
 virtual ~SixPlayerAreaFinder() = default;

 template_recognition::ScreenArea GetPlayerArea(PlayerLocation player_location) override;
 template_recognition::ScreenArea GetCardAreaLeft(PlayerLocation player_location) override;
 template_recognition::ScreenArea GetCardAreaRight(PlayerLocation player_location) override;
 template_recognition::ScreenArea GetMoneyArea(PlayerLocation player_location) override;
 template_recognition::ScreenArea GetTableArea(PlayerLocation player_location) override;
};

}  // namespace poker

#endif  // SIX_PLAYER_AREA_FINDER_H_
