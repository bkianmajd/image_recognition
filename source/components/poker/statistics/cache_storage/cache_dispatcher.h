#ifndef CACHE_DISPATCHER_H_
#define CACHE_DISPATCHER_H_

#include "components/poker/entities/card_def.h"
#include "components/poker/statistics/brute_force_generator/hand_generator.h"
#include "components/poker/statistics/brute_force_generator/table_generator.h"
#include "components/poker/statistics/cache_storage/cache_worker.h"
#include "components/poker/statistics/defs/defs.h"
#include "libraries/session_thread/session_thread.h"

#include "external_libraries/libchrome/base/message_loop/message_loop.h"
#include "external_libraries/libchrome/base/run_loop.h"

#include <thread>

namespace poker {
namespace statistics {

// maybe call this dispatcher preflop
class CacheDispatcher {
 public:
  // take in a single player hand here, with other parameters
  explicit CacheDispatcher(const PlayerHand& player_hand);

  HandStatistic Run();

 private:
  static constexpr size_t k_workerThreads = 8;

  // on thread complete callback
  void OnWorkerComplete(const WorkerResponse& worker_response);

  void UpdateMembers();

  void KickOffWorkerCalculation(size_t worker_index);

  void CreateWorkerThreads(
      scoped_refptr<base::SingleThreadTaskRunner> task_runner);

  void CloseWorkerAndMaybeEnd(size_t worker_index);

  PlayerHand player_hand_;
  std::vector<PlayerHand> opponent_hands_;
  std::vector<Table> table_combos_;

  // The opponent hand index
  unsigned int next_available_index_;

  std::array<SessionThread<CacheWorker>, k_workerThreads> worker_threads_;
  std::array<bool, k_workerThreads> is_worker_active_;

  uint64_t losing_count_;
  uint64_t tie_count_;
  uint64_t total_count_;

  base::Closure closure_;
};  // namespace statistics

}  // namespace statistics
}  // namespace poker

#endif  // CACHE_DISPATCHER_H_
