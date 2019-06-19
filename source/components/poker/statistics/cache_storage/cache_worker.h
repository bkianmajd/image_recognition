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
  uint64_t losing_count = 0;
  uint64_t tie_count = 0;
  uint64_t runs = 0;
  PlayerHand opponent_hand{};

  size_t worker_index;
};

using DispatcherCallback =
    base::Callback<void(const WorkerResponse& worker_response)>;

// A number of these get created and run in parallel
class CacheWorker {
 public:
  // take in a single player hand here, with other parameters
  CacheWorker(const std::vector<Table>& table_combos,
              scoped_refptr<base::SingleThreadTaskRunner> dispatch_poster,
              DispatcherCallback dispatcher_callback, size_t worker_index);

  void Calculate(const PlayerHand& player_hand,
                 const PlayerHand& opponent_hand);

 private:
  const size_t worker_index_;
  const std::vector<Table>& table_combos_;
  const DispatcherCallback dispatcher_callback_;
  scoped_refptr<base::SingleThreadTaskRunner> dispatch_poster_;
};

}  // namespace statistics
}  // namespace poker

#endif  // CACHE_WORKER_H_
