#include "components/poker/workflow_session_thread.h"

#include <cassert>
#include <functional>
#include <thread>

#include "components/poker/poker_game_controller/poker_game_controller.h"
#include "components/poker/poker_game_controller/training/training_game_controller.h"

#include "base/bind.h"
#include "base/message_loop/message_loop.h"

namespace poker {
namespace {}  // namespace

WorkflowSessionThread::WorkflowSessionThread() {}

WorkflowSessionThread::~WorkflowSessionThread() {
  if (thread_.has_value()) {
    EndSessionAndJoin();
  }
}

bool WorkflowSessionThread::StartSession() {
  if (thread_.has_value()) {
    std::cerr << "thread is in session" << std::endl;
    return false;
  }

  thread_ = std::thread(&WorkflowSessionThread::Session, this);
  assert(thread_.has_value());
  return true;
}

void WorkflowSessionThread::Session() {
  base::MessageLoop message_loop;
  base::RunLoop run_loop;
  closure_ = run_loop.QuitClosure();

  task_runner_ = message_loop.task_runner();
  run_loop.Run();
}

bool WorkflowSessionThread::EndSessionAndJoin() {
  if (!thread_.has_value()) {
    std::cerr << "thread has not started" << std::endl;
    return false;
  }

  // Edge case when thread starts and immediately is called close
  while (task_runner_ == nullptr) {
    base::PlatformThread::Sleep(base::TimeDelta::FromMicroseconds(500));
  }

  task_runner_->PostTask(FROM_HERE, closure_);

  // Reset thread state
  thread_->join();
  thread_.reset();
  task_runner_.reset();
  closure_.Reset();
  return true;
}

}  // namespace poker
