#ifndef MENU_RUNNER_H_
#define MENU_RUNNER_H_

#include "components/poker/workflow_session.h"
#include "helpers/directory_finder.h"

namespace poker {

class MenuRunner {
 public:
  explicit MenuRunner(SessionThread<WorkflowSession>* session);

  bool KeepRunning() const;
  void ProcessUserInput();

 private:
  void RecordSingleImage();
  void Record();
  void ShowMenu();
  PlayerHand QueryInjectedHand() const;

  SessionThread<WorkflowSession>* session_;

  bool keep_running_ = true;
  helpers::DirectoryFinder single_image_path_;
  helpers::DirectoryFinder recording_path_;

  int last_debug_number_ = 0;
};

}  // namespace poker

#endif  // MENU_RUNNER_H_
