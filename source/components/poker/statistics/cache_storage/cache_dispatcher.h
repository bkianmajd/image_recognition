#ifndef CACHE_STORAGE_H_
#define CACHE_STORAGE_H_

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

namespace {

constexpr size_t k_workerThreads = 8;

}  // namespace

// maybe call this dispatcher preflop
class CacheStorage {
 public:
  // take in a single player hand here, with other parameters
  CacheStorage(const PlayerHand& player_hand)
      : player_hand_(player_hand),
        next_available_index_(0),
        is_worker_active_({false}) {
    std::cout << "Calculating player hands: " << player_hand << std::endl;
  }

  HandStatistic Run() {
    // Start the RunLoop here
    base::MessageLoop message_loop;
    base::RunLoop run_loop;
    closure_ = run_loop.QuitClosure();

    UpdateMembers();

    CreateWorkerThreads(message_loop.task_runner());

    // run an array of threads

    // create the 1228 oponnent hand combos
    // dispatch each opponent hand combo to a single thread
    // mark the thread as active

    run_loop.Run();

    return losing_probability_;
  }

  // on thread complete callback
  void OnWorkerComplete(const WorkerResponse& worker_response) {
    // Store hand statistics
    losing_count_ += worker_response.losing_count;
    total_count_ += worker_response.runs;
    tie_count_ += worker_response.tie_count;

    // Update cout with relative remainding % complete
    std::cout << "[" << player_hand_.FirstCard() << "|"
              << player_hand_.SecondCard() << "] % complete: "
              << worker_response.runs / oponent_hands_.size() << std::endl;

    // run the 1228 oponnent hand combos by getting the next available one
    // TODO(BK): use similarities here
    KickOffWorkerCalculation(worker_response.worker_index);

    // the thread marked as active remove the one solved from the vector of
    // to store similar ones if the vector is empty, check to see if all threads
    // are complete if not mark this thread as idle
  }

 private:
  void UpdateMembers() {
    // The oponent cannot have any of these cards as they're already played
    std::vector<Card> exclusions;
    exclusions.push_back(player_hand_.FirstCard());
    exclusions.push_back(player_hand_.SecondCard());

    // Generate all possibilities of the opponents hand
    HandGenerator hand_generator(exclusions);
    opponent_hands_ = hand_generator.GenerateCombinations();

    // Generate all the combinations for the table
    TableGenerator table_generator(exclusions);
    table_combos_ =
        table_generator.GenerateCombinations();  // this takes a long time
  }

  void KickOffWorkerCalculation(size_t worker_index) {
    if(next_available_index_ >= opponent_hands_.size()) {
      // we are done, retire this worker
      CloseWorkerAndMaybeEnd(worker_index);
      return;
    }

    // Find opponent hand from vector
    PlayerHand opponent_hand = opponent_hands_[next_available_index_];
    next_available_index_++;


    // example of posting a task
    worker_threads_[worker_index].task_runner()->PostTask(
        FROM_HERE,
        base::Bind(&CacheWorker::Calculate,
                   base::Unretained(worker_threads_[worker_index].get()),
                   player_hand_, opponent_hand));
  }

  void CreateWorkerThreads(
      scoped_refptr<base::SingleThreadTaskRunner> task_runner) {
    DispatcherCallback callback =
        base::Bind(&CacheStorage::OnWorkerComplete, base::Unretained(this));
    for (size_t i = 0; i < k_workerThreads; ++i) {
      if (!worker_threads_[i].StartSession<CacheWorker>(
              table_combos_, task_runner, callback)) {
        std::cerr << "Failed to start session thread" << std::endl;
      }
      is_worker_active_[i] = true;
    }
  }

  void CloseWorkerAndMaybeEnd(size_t worker_index) {
    is_worker_active_[worker_index] = false;
    worker_threads_[worker_index].EndSessionAndJoin();

    // Check to see if all workers are inactive
    for(bool active : is_worker_active_) {
      if(active) {
        return;
      }
    }

    // By this point, all workers are inactive
    std::cout << "Completed calculation" << std::endl;
    // exit the message loop
    closure_.Run();
  }

  PlayerHand player_hand_;
  std::vector<PlayerHand> opponent_hands_;
  std::vector<Table> table_combos_;

  // The opponent hand index
  unsigned int next_available_index_;

  std::array<SessionThread<CacheWorker>, k_workerThreads> worker_threads_;
  std::array<bool, k_workerThreads> is_worker_active_;

  int losing_count_;
  int tie_count_;
  int total_count_;

  base::Closure closure_;
  double losing_probability_;
};

}  // namespace statistics
}  // namespace poker

#endif  // CACHE_STORAGE_H_
