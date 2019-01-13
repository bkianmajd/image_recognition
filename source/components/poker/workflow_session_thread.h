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

namespace poker {

class WorkflowSessionThread {
 public:
  WorkflowSessionThread();
  ~WorkflowSessionThread();

  bool StartSession();
  bool EndSessionAndJoin();

 private:
  void Session();

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  base::Closure closure_;
  base::Optional<std::thread> thread_;
};

}  // namespace poker

#endif  // WORKFLOW_SESSION_THREAD_H_
