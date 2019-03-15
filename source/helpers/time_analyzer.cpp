#include "helpers/time_analyzer.h"

#include <iostream>

namespace helpers {

TimeAnalyzer::TimeAnalyzer()
    : time_initialized_(std::chrono::system_clock::now()) {}

std::chrono::microseconds TimeAnalyzer::GetMicroseconds() const {
  std::chrono::time_point<std::chrono::system_clock> t2 =
      std::chrono::system_clock::now();

  return std::chrono::duration_cast<std::chrono::microseconds>(
      t2 - time_initialized_);
}

void TimeAnalyzer::Debug(const std::string& info) const {
  std::cout << info << "; microseconds: " << GetMicroseconds().count()
            << std::endl;
}

}  // namespace helpers
