#include "components/poker/statistics/cache_storage/cache_dispatcher.h"
#include "components/poker/statistics/cache_storage/preflop_similarities.h"

void CacheStorageThread() {

}

using namespace poker::statistics;


int main() {

  poker::PlayerHand player_hand;
  // Allocate threads
  poker::statistics::CacheStorage cache_storage(player_hand);


  // load the protobuf here
  // find the next available hand, print the total size needed to solve, starts at 1328
  // create objects

  // in for loop
    // Create cache storage
    // Call Run, which returns the losing probability
    //print out message
    // Get similars and then return the protofile
  //

  return 0;
}
