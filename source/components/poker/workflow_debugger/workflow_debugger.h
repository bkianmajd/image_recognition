#ifndef WORKFLOW_DEBUGGER_H_
#define WORKFLOW_DEBUGGER_H_

#include "gtest/gtest_prod.h"

#include "components/poker/entities/game_model_def.h"
#include "components/poker/workflow_debugger/workflow_debugger_interface.h"
#include "helpers/directory_finder.h"

namespace poker {

enum DebugType {
  PRINT_GAME_MODEL,
  PRINT_WORKFLOW_MODEL,
};

/// Class that deals with printing and displaying workflow callbacks
class WorkflowDebugger : public WorkflowDebuggerInterface {
 public:
  explicit WorkflowDebugger(DebugType debug_type);

  void StoreError(const image::Image& image_error,
                  const std::string& error_str) override;

  void PrintNewHand(const GameModel& game_model) override;

  void PrintStatusChange(const GameModel& game_model) override;

  void PrintDecision() override;

  void PrintStatusChange(const WorkflowModel& game_model) override;

 private:
  FRIEND_TEST(WorkflowDebuggerTest, ErrorTest);
  void PrintDealerCards(const std::array<Card, DEALER_MAX_SIZE>& dealer_cards) const;

  void ResetLogFile();

  // member variable for PrintStatusChange
  int status_change_counter_;
  // MemberVariable for StoreError
  int error_identifier_;
  helpers::DirectoryFinder error_log_directory_;
  DebugType debug_type_;
};

}  // namespace poker

#endif  // WORKFLOW_DEBUGGER_H_
