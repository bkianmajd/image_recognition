#include "components/poker/workflow_session_thread.h"

#include <cassert>
#include <functional>
#include <thread>

#include "components/poker/poker_game_controller/poker_game_controller.h"
#include "components/poker/poker_game_controller/training/training_game_controller.h"
#include "helpers/file_manager.h"

#include "base/bind.h"
#include "base/message_loop/message_loop.h"

namespace poker {
namespace {

constexpr char kDebugImageLocation[] = "components/poker/menu_runner/images";

}  // namespace

WorkflowSessionThread::WorkflowSessionThread() : recording_(false) {}

WorkflowSessionThread::~WorkflowSessionThread() {
  if (thread_.has_value()) {
    EndSessionAndJoin();
  }
}

bool WorkflowSessionThread::StartSession() {
  std::lock_guard<std::mutex> lg(mutex_);
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

  // Start the session
  workflow_session_ = std::make_unique<WorkflowSession>(task_runner_);

  run_loop.Run();

  // Destruct the object
  workflow_session_.reset();
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

bool WorkflowSessionThread::ProcessImage(const image::Image& image) {
  if (!thread_.has_value()) {
    std::cerr << "Can only be called after session has started" << std::endl;
    return false;
  }

  // Copy the last image for function call |SaveImageToDebug|
  {
    std::lock_guard<std::mutex> lg(mutex_);
    last_image_ = image;
  }

  while (workflow_session_ == nullptr) {
    base::PlatformThread::Sleep(base::TimeDelta::FromMicroseconds(500));
  }

  task_runner_->PostTask(
      FROM_HERE, base::Bind(&WorkflowSession::ProcessImage,
                            base::Unretained(workflow_session_.get()), image));
  return true;
}

void WorkflowSessionThread::SaveImageToDebug() {
  helpers::DirectoryFinder directory =
      helpers::CreateDirectoryFinderFromWorkspace(kDebugImageLocation);
  // Create the file name
  std::stringstream ss;
  ss << last_debug_number_ << ".jpg";
  last_debug_number_++;
  std::string file_abs_path = directory.GetAbsPathOfTargetFile(ss.str());

  // Write last image to file
  std::lock_guard<std::mutex> lg(mutex_);
  helpers::FileManager::StoreFile(last_image_.data(), last_image_.size(),
                                  file_abs_path);
}

void WorkflowSessionThread::InjectNextPlayerCard(
    const PlayerHand& player_hand) {
  std::lock_guard<std::mutex> lg(mutex_);
  if (!workflow_session_) {
    std::cerr << "Session is not established" << std::endl;
    return;
  }
  task_runner_->PostTask(
      FROM_HERE,
      base::Bind(&WorkflowSession::InjectNewHand,
                 base::Unretained(workflow_session_.get()), player_hand));
}

void WorkflowSessionThread::ClearInjection() {
  std::lock_guard<std::mutex> lg(mutex_);
  if (!workflow_session_) {
    std::cerr << "Session is not established" << std::endl;
    return;
  }
  task_runner_->PostTask(FROM_HERE,
                         base::Bind(&WorkflowSession::ClearInjection,
                                    base::Unretained(workflow_session_.get())));
}

void WorkflowSessionThread::ForceDecision() {
  std::lock_guard<std::mutex> lg(mutex_);
  if (!workflow_session_) {
    std::cerr << "Session is not established" << std::endl;
    return;
  }
  task_runner_->PostTask(FROM_HERE,
                         base::Bind(&WorkflowSession::ForceDecision,
                                    base::Unretained(workflow_session_.get())));
}

void WorkflowSessionThread::RecordImages() {
  recording_.store(true);
  recording_start_time_ = std::chrono::system_clock::now();
}

}  // namespace poker
