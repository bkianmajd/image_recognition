#ifndef WORKFLOW_DEBUGGER_INTERFACE_H_
#define WORKFLOW_DEBUGGER_INTERFACE_H_

#include "components/poker/entities/game_model_def.h"
#include "libraries/image_def/image_def.h"

namespace poker {

class WorkflowDebuggerInterface {
 public:
  virtual ~WorkflowDebuggerInterface() = default;
  virtual void StoreError(const image::Image& image_error, const std::string& error_str) = 0;
  virtual void PrintNewHand(const GameModel& game_model) = 0;
  virtual void PrintStatusChange(const GameModel& game_model) = 0;
  virtual void PrintDecision() = 0;
};

}  // namespace poker

#endif  // WORKFLOW_DEBUGGER_INTERFACE_H_
