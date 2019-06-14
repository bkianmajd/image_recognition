#include "components/poker/statistics/cache_manager/cache_manager.h"

namespace poker {
namespace statistics {

CacheManager::CacheManager(const helpers::DirectoryFinder& directory_finder,
                           const std::string& preflop_file_name,
                           const std::string& postflop_file_name)
    : initialized_(false),
      preflop_loader_(directory_finder, preflop_file_name),
      postflop_loader_(directory_finder, postflop_file_name) {}

CacheManager::~CacheManager() {
  if (initialized_) {
    ShutdownStore();
  }
}

void CacheManager::InitializeLoad() {
  if (initialized_) {
    return;
  }
  initialized_ = true;
  PreflopStatistics preflop_statistics;
  PostFlopStatistics post_flop_statistics;

  // convert to map for |preflop_map_|
  preflop_loader_.LoadProtobuf(&preflop_statistics);
  for (int i = 0; i < preflop_statistics.preflop_statistics_size(); ++i) {
    int index =
        preflop_statistics.mutable_preflop_statistics(i)->hand_sorted_id();
    double value =
        preflop_statistics.mutable_preflop_statistics(i)->losing_probability();
    preflop_map_[index] = value;
  }

  // convert to map for |postflop_map_|
  postflop_loader_.LoadProtobuf(&post_flop_statistics);
  for (int i = 0; i < post_flop_statistics.post_flop_statistics_size(); ++i) {
    int64_t index = post_flop_statistics.mutable_post_flop_statistics(i)
                        ->hand_table_unique_id();
    double value = post_flop_statistics.mutable_post_flop_statistics(i)
                       ->losing_probability();
    postflop_map_[index] = value;
  }
}

void CacheManager::ShutdownStore() {
  // Preventing a reset of the data by doing an early return
  if (!initialized_) {
    std::cerr << "trying to shutdown before loading" << std::endl;
    return;
  }
  initialized_ = false;

  // unload from map to protobuf
  PreflopStatistics preflop_statistics;
  PostFlopStatistics post_flop_statistics;

  // unloading from |preflop_map_|
  auto pre_it = preflop_map_.begin();
  while (pre_it != preflop_map_.end()) {
    PreFlopStatistic* ptr = preflop_statistics.add_preflop_statistics();
    ptr->set_hand_sorted_id(pre_it->first);
    ptr->set_losing_probability(pre_it->second);
    pre_it++;
  }

  // unloading from |postflop_map_|
  auto post_it = postflop_map_.begin();
  while (post_it != postflop_map_.end()) {
    PostFlopStatistic* ptr = post_flop_statistics.add_post_flop_statistics();
    ptr->set_hand_table_unique_id(post_it->first);
    ptr->set_losing_probability(post_it->second);
    post_it++;
  }

  preflop_loader_.StoreProtobuf(preflop_statistics);
  postflop_loader_.StoreProtobuf(post_flop_statistics);
}

base::Optional<double> CacheManager::GetLosingProbability(
    const PlayerHand& player_hand) {
  // return early becasue we haven't loaded the protobuf
  if (!initialized_) {
    return base::nullopt;
  }

  // Sort
  SortedId hand_sorted_id = static_cast<SortedId>(player_hand.UniqueId());

  auto it = preflop_map_.find(hand_sorted_id);
  if (it == preflop_map_.end()) {
    return base::nullopt;
  }

  return it->second;
}

void CacheManager::Reset() {
  initialized_ = true;
  preflop_map_.clear();
  postflop_map_.clear();
  ShutdownStore();
}

bool CacheManager::HasInitialized() const { return initialized_; }

void CacheManager::StoreLosingProbability(const PlayerHand& player_hand,
                                          double probability) {
  if (!initialized_) {
    return;
  }
  SortedId hand_sorted_id = static_cast<SortedId>(player_hand.UniqueId());

  preflop_map_[hand_sorted_id] = probability;
}

base::Optional<double> CacheManager::GetLosingProbability(
    const std::vector<Card>& hand_cards, const std::vector<Card>& table_cards) {
  // return early becasue we haven't loaded the protobuf
  if (!initialized_) {
    return base::nullopt;
  }
  // TODO: Replace this with a table of tables
/*
  SortedId hand_sorted_id = static_cast<SortedId>(CardsToUniqueId(hand_cards));
  SortedId table_sorted_id =
      static_cast<SortedId>(CardsToUniqueId(table_cards));

  PostFlopSortedId post_flop_id =
      ConvertToSortedId(hand_sorted_id, table_sorted_id);
  auto it = postflop_map_.find(post_flop_id);
  if (it == postflop_map_.end()) {
    return base::nullopt;
  }

  return it->second;
*/
}

void CacheManager::StoreLosingProbability(const std::vector<Card>& hand_cards,
                                          const std::vector<Card>& table_cards,
                                          double probability) {
  // return early becasue we haven't loaded the protobuf
  if (!initialized_) {
    return;
  }
/*
  SortedId hand_sorted_id = static_cast<SortedId>(CardsToUniqueId(hand_cards));
  SortedId table_sorted_id =
      static_cast<SortedId>(CardsToUniqueId(table_cards));

  PostFlopSortedId post_flop_id =
      ConvertToSortedId(hand_sorted_id, table_sorted_id);
  postflop_map_[post_flop_id] = probability;
*/
}

CacheManager::PostFlopSortedId CacheManager::ConvertToSortedId(
    int hand_sorted_id, int table_sorted_id) {
  // the last 6 digits are composed of table_sorted id
  constexpr int64_t kOffset = 1000000;
  return hand_sorted_id * kOffset + table_sorted_id;
}

}  // namespace statistics
}  // namespace poker
