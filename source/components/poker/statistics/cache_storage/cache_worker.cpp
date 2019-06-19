#include "components/poker/statistics/cache_storage/cache_worker.h"

namespace poker {
namespace statistics {

// take in a single player hand here, with other parameters
CacheWorker::CacheWorker(
    const std::vector<Table>& table_combos,
    scoped_refptr<base::SingleThreadTaskRunner> dispatch_poster,
    DispatcherCallback dispatcher_callback, size_t worker_index)
    : worker_index_(worker_index),
      table_combos_(table_combos),
      dispatcher_callback_(dispatcher_callback),
      dispatch_poster_(dispatch_poster) {}

void CacheWorker::Calculate(const PlayerHand& player_hand,
                            const PlayerHand& opponent_hand) {
  std::vector<Card> exclusions;
  exclusions.push_back(player_hand.FirstCard());
  exclusions.push_back(player_hand.SecondCard());
  exclusions.push_back(opponent_hand.FirstCard());
  exclusions.push_back(opponent_hand.SecondCard());
  TableGeneratorIterator table_iterator(exclusions, table_combos_);

  // Create the counters
  uint64_t losing_count = 0;
  uint64_t tie_count = 0;
  uint64_t total_count = 0;

  // Find the winner:
  const Table* table = table_iterator.Next();
  while (table != nullptr) {
    simulator::GameResult game_result =
        simulator::ModeratePlayerWon(player_hand, opponent_hand, *table);
    if (game_result == simulator::GAME_RESULT_LOST) {
      losing_count++;
    }
    if (game_result == simulator::GAME_RESULT_TIE) {
      tie_count++;
    }
    total_count++;

    // Iterate the next table
    table = table_iterator.Next();
  }

  WorkerResponse workerResponse{};
  workerResponse.losing_count = losing_count;
  workerResponse.tie_count = tie_count;
  workerResponse.opponent_hand = opponent_hand;
  workerResponse.runs = total_count;
  workerResponse.worker_index = worker_index_;

  auto callback_runner = base::Bind(dispatcher_callback_, workerResponse);
  dispatch_poster_->PostTask(FROM_HERE, callback_runner);
}

}  // namespace statistics
}  // namespace poker
