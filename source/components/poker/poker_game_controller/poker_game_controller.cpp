#include "components/poker/poker_game_controller/poker_game_controller.h"

namespace poker {
namespace {

// generate mocks here through a factory

}  // namespace

PokerGameController::PokerGameController(
    const PokerWorkflowCallbacks& poker_workflow_callbacks, bool unit_testing)
    : poker_workflow_callbacks_(poker_workflow_callbacks) {}

void ProcessBigImage(const std::vector<char>& big_image_raw_data) {
  // TODO - CALL the image pipeline
  // Call the mocks to invoke callbacks
  // Unit test that the mocks are called
}

}  // namespace poker
