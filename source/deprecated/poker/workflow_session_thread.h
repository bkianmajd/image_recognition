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
#include "components/poker/workflow_session.h"
#include "libraries/image_def/image_def.h"

namespace poker {

class WorkflowSessionThread {
 public:
  WorkflowSessionThread();
  ~WorkflowSessionThread();

  bool StartSession();
  bool EndSessionAndJoin();

  // API functions
  bool ProcessImage(const image::Image& image);
  void SaveImageToDebug();

  /// Injects what card the dealer deals to the player. This overwrites what the
  /// game controller sees.
  void InjectNextPlayerCard(const PlayerHand& player_hand);
  void ClearInjection();

  /// Runs the statistics to decide and prints the results
  void ForceDecision();

  /// Record images for 30 seconds
  void RecordImages();

 private:
  void Session();

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  base::Closure closure_;
  base::Optional<std::thread> thread_;
  std::unique_ptr<WorkflowSession> workflow_session_;

  std::mutex mutex_;
  image::Image last_image_;
  int last_debug_number_ = 0;
  std::atomic_bool recording_;
  std::chrono::time_point<std::chrono::system_clock> recording_start_time_;
};

}  // namespace poker

#endif  // WORKFLOW_SESSION_THREAD_H_
