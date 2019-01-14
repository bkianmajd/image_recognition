#ifndef WORKFLOW_SESSION_THREAD_H_
#define WORKFLOW_SESSION_THREAD_H_

#include <memory>
#include <mutex>
#include <thread>

#include <base/memory/scoped_refptr.h>
#include <base/optional.h>
#include <base/single_thread_task_runner.h>
#include <base/task_runner.h>

#include "components/poker/poker_game_controller/poker_game_controller_interface.h"
#include "libraries/image_def/image_def.h"
#include "components/poker/workflow_session.h"

namespace poker {

class WorkflowSessionThread {
 public:
  WorkflowSessionThread();
  ~WorkflowSessionThread();

  bool StartSession();
  bool EndSessionAndJoin();
  bool ProcessImage(const image::Image& image) const;

 private:
  void Session();

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  base::Closure closure_;
  base::Optional<std::thread> thread_;
  std::unique_ptr<WorkflowSession> workflow_session_;
};

}  // namespace poker

#endif  // WORKFLOW_SESSION_THREAD_H_
