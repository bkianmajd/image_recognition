#ifndef WORKFLOW_SESSION_H_
#define WORKFLOW_SESSION_H_

#include <memory>
#include <mutex>

#include "components/poker/entities/poker_workflow_callbacks.h"
#include "components/poker/poker_game_controller/poker_game_controller_interface.h"
#include "components/poker/workflow_debugger/workflow_debugger_interface.h"
#include "libraries/image_def/image_def.h"
#include "libraries/session_thread/session_thread.h"

namespace poker {

/// High level poker workflow. Instantiated from WorkflowSessionThread
class WorkflowSession {
 public:
  explicit WorkflowSession(
      scoped_refptr<base::SingleThreadTaskRunner> workflow_task_runner);

  /// Process the image and start the image pipeline
  void ProcessImage(const image::Image& big_image_raw_data);

 private:
  // Updates from the poker game controller thread
  void OnNewHand(const GameModel& game_model);
  void OnGameModelUpdate(const GameModel& game_model);
  void OnPokerDecision();
  void OnError(const image::Image& error_image, const std::string& error_str);

  // Entities
  GameModel game_model_;

  // The workflow's thread corresponding taskrunner
  scoped_refptr<base::SingleThreadTaskRunner> workflow_task_runner_;

  // Interactors
  SessionThread<PokerGameControllerInterface> game_controller_session_;
  std::unique_ptr<WorkflowDebuggerInterface> workflow_debugger_;
};

}  // namespace poker

#endif  // WORKFLOW_SESSION_H_
