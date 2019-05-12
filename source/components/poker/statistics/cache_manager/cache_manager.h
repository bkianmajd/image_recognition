#ifndef CACHE_MANAGER_H_
#define CACHE_MANAGER_H_

#include <unordered_map>

#include "components/poker/entities/card_def.h"
#include "components/poker/statistics/cache_manager/proto/poker_statistics.pb.h"
#include "external_libraries/libchrome/base/optional.h"
#include "gtest/gtest_prod.h"
#include "helpers/directory_finder.h"
#include "libraries/protobuf_loader/protobuf_loader.h"

namespace poker {
namespace statistics {

class CacheManager {
 public:
  CacheManager(const helpers::DirectoryFinder& directory_finder,
               const std::string& preflop_file_name,
               const std::string& postflop_file_name);

  ~CacheManager();

  // Resets the binary data file
  void Reset();

  bool HasInitialized() const;

  void InitializeLoad();

  void ShutdownStore();

  base::Optional<double> GetLosingProbability(const Card& left,
                                              const Card& right);

  void StoreLosingProbability(const Card& left, const Card& right,
                              double probability);

  base::Optional<double> GetLosingProbability(
      const std::vector<Card>& hand_cards,
      const std::vector<Card>& table_cards);

  void StoreLosingProbability(const std::vector<Card>& hand_cards,
                              const std::vector<Card>& table_cards,
                              double probability);

 private:
  FRIEND_TEST(CacheManagerTest, LoadTest);
  FRIEND_TEST(CacheManagerTest, ShutdownTest);
  FRIEND_TEST(CacheStorageTest, PreflopTest);

  using SortedId = int;
  using PostFlopSortedId = int64_t;
  using LosingProbability = double;

  // This is a custom SortedId for the cache manager. Order of the hand and
  // table matters, and are unique. E.g. Player has Ace Two, Table has 3 4 5...
  // is different than Player has 4 5, Table has Three Ace Two.
  PostFlopSortedId ConvertToSortedId(int hand_sorted_id, int table_sorted_id);

  bool initialized_;
  std::unordered_map<SortedId, LosingProbability> preflop_map_;
  std::unordered_map<PostFlopSortedId, LosingProbability> postflop_map_;
  proto::ProtobufLoader preflop_loader_;
  proto::ProtobufLoader postflop_loader_;
};

}  // namespace statistics
}  // namespace poker

#endif  // CACHE_MANAGER_H_
