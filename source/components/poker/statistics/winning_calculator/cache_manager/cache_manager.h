#ifndef CACHE_MANAGER_H_
#define CACHE_MANAGER_H_

#include "components/poker/statistics/winning_calculator/cache_manager/compiled_files/poker_statistics.pb.h"

#include <iostream>
#include <fstream>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

namespace poker {
namespace statistics {
class CacheManager {
 public:
  CacheManager();

 private:
  void RetreiveTable() {

   google::protobuf::io::FileInputStream input();
   std::fstream fs("test");
   fs.fd;

   google::protobuf::io::StringOutputStream s;
  }

  poker::PreflopStatistics preflop_statistics_;

};

}  // statistics
}  // poker

#endif  // CACHE_MANAGER_H_
