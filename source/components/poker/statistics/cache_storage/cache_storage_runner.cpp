#include <QCoreApplication>

#include "components/poker/statistics/brute_force_generator/hand_generator.h"
#include "components/poker/statistics/cache_storage/cache_dispatcher.h"
#include "components/poker/statistics/cache_storage/preflop_similarities.h"
#include "components/poker/statistics/cache_storage/proto/poker_statistics.pb.h"
#include "helpers/time_analyzer.h"
#include "libraries/protobuf_loader/cache_manager.h"

const std::string kCacheDirectory =
    "components/poker/statistics/cache_storage/binary_data";

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  // Create all the possible starting hands
  poker::statistics::HandGenerator hand_generator(std::vector<poker::Card>{});
  std::vector<poker::PlayerHand> hands = hand_generator.GenerateCombinations();

  // Find the next available hand
  for (size_t i = 0; i < hands.size(); ++i) {
    // load the protobuf here
    proto::CacheManager<poker::PreFlopStatistic> cache_manager(
        helpers::CreateDirectoryFinderFromWorkspace(kCacheDirectory));
    poker::PreFlopStatistic* preflop_statistic = cache_manager.Get();
    auto* map = preflop_statistic->mutable_losing_probability_map();

    std::cout << "A total of " << map->size() << " out of " << hands.size()
              << " are solved" << std::endl;

    poker::PlayerHand& player_hand = hands[i];

    // ----- Debug1 ----
//    player_hand.FirstCard() =
//        poker::Card(poker::CardValue::CARD_VALUE_ACE, poker::Suit::SUIT_SPADE);
//    player_hand.SecondCard() =
//        poker::Card(poker::CardValue::CARD_VALUE_NINE, poker::Suit::SUIT_SPADE);
    // ----- override ----

    auto it = map->find(player_hand.UniqueId());
    if (it != map->end()) {
      std::cout << "Player hand already complete: " << player_hand << std::endl;
      std::cout << "losing prob: " << it->second.losing_probability()
                << " tying prob: " << it->second.tie_probability() << std::endl;
      // Skip this case because its already loaded
      continue;
    }

    // ----- Debug2 ----
//    player_hand.FirstCard() =
//        poker::Card(poker::CardValue::CARD_VALUE_ACE, poker::Suit::SUIT_SPADE);
//    player_hand.SecondCard() =
//        poker::Card(poker::CardValue::CARD_VALUE_EIGHT, poker::Suit::SUIT_SPADE);
    // ----- override ----

    // Run the statistic
    std::cout << "Caclulating player hand: " << player_hand << std::endl;
    helpers::TimeAnalyzer time_analyzer;
    poker::statistics::CacheDispatcher cache_dispatcher(player_hand);
    std::flush(std::cout);
    // this takes a very long time
    poker::statistics::HandStatistic hand_statistic = cache_dispatcher.Run();

    // print out some metrics
    std::cout << "Calculating player hand complete: " << player_hand
              << std::endl;
    time_analyzer.Debug("Timing: ");
    std::cout << "losing prob: " << hand_statistic.losing_probability
              << " tying prob: " << hand_statistic.tie_probability << std::endl;

    // Find similarities
    poker::statistics::PreflopSimilarities preflopSim;
    std::vector<poker::PlayerHand> similar_hands =
        preflopSim.GetSimilarities(player_hand);

    // Store hand into map
    poker::Statistic statistic;
    statistic.set_losing_probability(hand_statistic.losing_probability);
    statistic.set_tie_probability(hand_statistic.tie_probability);
    (*map)[player_hand.UniqueId()] = statistic;
    // Store similar hand into map
    for (const poker::PlayerHand& player_hand : similar_hands) {
      (*map)[player_hand.UniqueId()] = statistic;
    }
    std::cout << "------------------------------------------" << std::endl;
  }

  return 0;
}
