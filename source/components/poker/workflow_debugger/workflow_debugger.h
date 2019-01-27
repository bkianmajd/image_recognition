#ifndef WORKFLOW_DEBUGGER_H_
#define WORKFLOW_DEBUGGER_H_

#include "gtest/gtest_prod.h"

#include "components/poker/entities/game_model_def.h"
#include "components/poker/workflow_debugger/workflow_debugger_interface.h"
#include "helpers/directory_finder.h"

namespace poker {

/// Class that deals with printing and displaying workflow callbacks
class WorkflowDebugger : public WorkflowDebuggerInterface {
 public:
  WorkflowDebugger();

  void StoreError(const image::Image& image_error,
                  const std::string& error_str);

  void PrintNewHand(const GameModel& game_model);

  void PrintStatusChange(const GameModel& game_model);

  void PrintDecision();

 private:
  FRIEND_TEST(WorkflowDebuggerTest, ErrorTest);

  void ResetLogFile();

  // member variable for PrintStatusChange
  int status_change_counter_;
  // MemberVariable for StoreError
  int error_identifier_;
  helpers::DirectoryFinder error_log_directory_;
};

}  // namespace poker

#endif  // WORKFLOW_DEBUGGER_H_
