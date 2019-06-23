#include "components/poker/statistics/cache_storage/cache_dispatcher.h"

namespace poker {
namespace statistics {

CacheDispatcher::CacheDispatcher(const PlayerHand& player_hand)
    : player_hand_(player_hand),
      next_available_index_(0),
      is_worker_active_({false}),
      losing_count_(0),
      tie_count_(0),
      total_count_(0) {
  std::cout << "Cache dispatcher constructed: " << player_hand << std::endl;
}

HandStatistic CacheDispatcher::Run() {
  // Start the RunLoop here
  base::MessageLoop message_loop;
  base::RunLoop run_loop;
  closure_ = run_loop.QuitClosure();

  // create the 1228 oponnent hand combos and reset the counter
  UpdateMembers();

  // run an array of threads
  CreateWorkerThreads(message_loop.task_runner());

  // dispatch each opponent hand combo to a single thread
  // mark the thread as active
  for (size_t worker_index = 0; worker_index < worker_threads_.size();
       ++worker_index) {
    if (next_available_index_ < opponent_hands_.size()) {
      KickOffWorkerCalculation(worker_index);
    } else {
      // we are done, retire this worker
      CloseWorkerAndMaybeEnd(worker_index);
    }
  }

  run_loop.Run();

  // All worker threads are complete. Calculate the losing probability
  HandStatistic hand_statistic;
  hand_statistic.tie_probability =
      static_cast<double>(tie_count_) / static_cast<double>(total_count_);
  hand_statistic.losing_probability =
      static_cast<double>(losing_count_) / static_cast<double>(total_count_);

  return hand_statistic;
}

void CacheDispatcher::OnWorkerComplete(const WorkerResponse& worker_response) {
  // check for overflow
  uint64_t prev_total_count = total_count_;

  // Store hand statistics
  losing_count_ += worker_response.losing_count;
  total_count_ += worker_response.runs;
  tie_count_ += worker_response.tie_count;

  if (total_count_ < prev_total_count) {
    std::cerr << "overflow" << std::endl;
    assert(true);
  }

  // Update cout with relative remainding % complete
  std::cout << "[" << worker_response.opponent_hand.FirstCard() << "|"
            << worker_response.opponent_hand.SecondCard() << "] % complete: "
            << static_cast<double>(next_available_index_) /
                   static_cast<double>(opponent_hands_.size())
            << " ; losing prob/tie prob: "
            << static_cast<double>(worker_response.losing_count) /
                   static_cast<double>(worker_response.runs)
            << " / "
            << static_cast<double>(worker_response.tie_count) /
                   static_cast<double>(worker_response.runs)
            << std::endl;

  if (next_available_index_ >= opponent_hands_.size()) {
    // we are done, retire this worker
    CloseWorkerAndMaybeEnd(worker_response.worker_index);
    return;
  }

  // run the 1228 oponnent hand combos by getting the next available one
  // TODO(BK): use similarities here
  KickOffWorkerCalculation(worker_response.worker_index);
}

void CacheDispatcher::UpdateMembers() {
  // The oponent cannot have any of these cards as they're already played
  std::vector<Card> exclusions;
  exclusions.push_back(player_hand_.FirstCard());
  exclusions.push_back(player_hand_.SecondCard());

  // Zero all the fields
  losing_count_ = 0;
  tie_count_ = 0;
  total_count_ = 0;

  // Generate all possibilities of the opponents hand
  HandGenerator hand_generator(exclusions);
  opponent_hands_ = hand_generator.GenerateCombinations();

  // Generate all the combinations for the table
  TableGenerator table_generator(exclusions);
  table_combos_ =
      table_generator.GenerateCombinations();  // this takes a long time
}

void CacheDispatcher::KickOffWorkerCalculation(size_t worker_index) {
  // assert that next_available_index < opponent_hands size

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

void CacheDispatcher::CreateWorkerThreads(
    scoped_refptr<base::SingleThreadTaskRunner> task_runner) {
  DispatcherCallback callback =
      base::Bind(&CacheDispatcher::OnWorkerComplete, base::Unretained(this));
  for (size_t i = 0; i < k_workerThreads; ++i) {
    if (!worker_threads_[i].StartSession<CacheWorker>(
            table_combos_, task_runner, callback, i)) {
      std::cerr << "Failed to start session thread" << std::endl;
    }
    is_worker_active_[i] = true;
  }
}

void CacheDispatcher::CloseWorkerAndMaybeEnd(size_t worker_index) {
  worker_threads_[worker_index].EndSessionAndJoin();
  is_worker_active_[worker_index] = false;

  // Check to see if all workers are inactive
  for (bool active : is_worker_active_) {
    if (active) {
      return;
    }
  }

  // By this point, all workers are inactive
  std::cout << "Completed calculation 100%" << std::endl;
  // exit the message loop
  closure_.Run();
}

}  // namespace statistics
}  // namespace poker
