#ifndef WORKFLOW_DEBUGGER_MOCK_H_
#define WORKFLOW_DEBUGGER_MOCK_H_

#include "components/poker/workflow_debugger/workflow_debugger_interface.h"

namespace poker {

/// Class that deals with printing and displaying workflow callbacks
class WorkflowDebuggerMock : public WorkflowDebuggerInterface {
 public:
  WorkflowDebuggerMock() = default;
  ~WorkflowDebuggerMock() override = default;

  void StoreError(const image::Image& image_error,
                  const std::string& error_str) override {
    (void)image_error;
    (void)error_str;
  }
  void PrintNewHand(const GameModel& game_model) override { (void)game_model; }
  void PrintStatusChange(const GameModel& game_model) override {
    (void)game_model;
  }
  void PrintDecision() override {}
  void PrintStatusChange(const WorkflowModel& game_model) override {
    (void)game_model;
  }
};

}  // namespace poker

#endif  // WORKFLOW_DEBUGGER_MOCK_H_
