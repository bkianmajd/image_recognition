#ifndef CACHE_WORKER_H_
#define CACHE_WORKER_H_

#include "components/poker/entities/card_def.h"
#include "components/poker/simulator/defs/game_moderator.h"
#include "components/poker/statistics/brute_force_generator/hand_generator.h"
#include "components/poker/statistics/brute_force_generator/table_generator.h"
#include "components/poker/statistics/brute_force_generator/table_generator_iterator.h"

#include "external_libraries/libchrome/base/bind.h"
#include "external_libraries/libchrome/base/message_loop/message_loop.h"

#include <thread>

namespace poker {
namespace statistics {

struct WorkerResponse {
  size_t losing_count = 0;
  size_t tie_count = 0;
  size_t runs = 0;
  PlayerHand opponent_hand{};

  int worker_index;
};

using DispatcherCallback =
    base::Callback<void(const WorkerResponse& worker_response)>;

// A number of these get created and run in parallel
class CacheWorker {
 public:
  // take in a single player hand here, with other parameters
  CacheWorker(const std::vector<Table>& table_combos,
              scoped_refptr<base::SingleThreadTaskRunner> dispatch_poster,
              DispatcherCallback dispatcher_callback, int worker_index)

      : worker_index_(worker_index),
        table_combos_(table_combos),
        dispatch_poster_(dispatch_poster),
        dispatcher_callback_(dispatcher_callback) {}

  void Calculate(const PlayerHand& player_hand,
                 const PlayerHand& opponent_hand) {
    std::vector<Card> exclusions;
    exclusions.push_back(player_hand.FirstCard());
    exclusions.push_back(player_hand.SecondCard());
    exclusions.push_back(opponent_hand.FirstCard());
    exclusions.push_back(opponent_hand.SecondCard());
    TableGeneratorIterator table_iterator(exclusions, table_combos_);

    // Create the counters
    size_t losing_count = 0;
    size_t tie_count = 0;
    size_t total_count = 0;

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
      if (game_result != simulator::GAME_RESULT_TIE) {
        total_count++;
      }

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

 private:
  const int worker_index_;
  const std::vector<Table>& table_combos_;

  scoped_refptr<base::SingleThreadTaskRunner> dispatch_poster_;
  DispatcherCallback dispatcher_callback_;
};

}  // namespace statistics
}  // namespace poker

#endif  // CACHE_WORKER_H_
