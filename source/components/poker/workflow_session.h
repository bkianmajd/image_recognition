#ifndef WORKFLOW_SESSION_H_
#define WORKFLOW_SESSION_H_

#include <memory>
#include <mutex>

#include "components/poker/entities/poker_workflow_callbacks.h"
#include "components/poker/poker_game_controller/poker_game_controller_interface.h"
#include "components/poker/workflow_debugger/workflow_debugger_interface.h"
#include "components/poker/workflow_model_builder.h"
#include "libraries/image_def/image_def.h"
#include "libraries/session_thread/session_thread.h"
#include "poker_decider/poker_decider_interface.h"

namespace poker {

/// High level poker workflow. Instantiated from WorkflowSessionThread
class WorkflowSession {
 public:
  WorkflowSession();

  /// Process the image and start the image pipeline
  void ProcessImage(const image::Image& big_image_raw_data);

  /// Injects a new hand from the menu runner for debugging purposes
  void InjectNewHand(const PlayerHand& player_hand);

  /// For debugging purposes, called from the menu runner
  void ForceDecision();

  /// For debugging purposes, called from the menu runner
  void ClearInjection();

  /// For debugging purposes, called from the menu runner
  void SaveImageToDebug(const std::string& file_path_name);

 private:
  // Updates from the poker game controller thread
  void OnNewHand(const GameModel& game_model);
  void OnGameModelUpdate(const GameModel& game_model);
  void OnPokerDecision();
  void OnError(const image::Image& error_image, const std::string& error_str);

  // Entities
  std::unique_ptr<WorkflowModelBuilder> workflow_model_builder_;

  // Interactors
  std::unique_ptr<PokerGameControllerInterface> game_controller_;

  // Poker DecierInterface
  std::unique_ptr<PokerDeciderInterface> poker_decider_interface_;

  // For debugging
  std::unique_ptr<WorkflowDebuggerInterface> workflow_debugger_;
  base::Optional<PlayerHand> injected_hand_;

  image::Image last_image_;
  bool recorded_ = false;
};

}  // namespace poker

#endif  // WORKFLOW_SESSION_H_
