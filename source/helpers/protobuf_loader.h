#ifndef TIME_ANALYZER_H_
#define TIME_ANALYZER_H_

#include <chrono>
#include <string>

#define STR2(X) #X
#define STR(X) STR2(X)

#define CAT2(X, Y) X##Y
#define CAT(X, Y) CAT2(X, Y)

#define TIME_ANALYZE(X)                   \
  helpers::TimeAnalyzer CAT(t, __LINE__); \
  X;                                      \
  CAT(t, __LINE__).Debug(#X);

namespace helpers {
/// This class measures a specific time
class TimeAnalyzer {
 public:
  TimeAnalyzer();
  TimeAnalyzer(const TimeAnalyzer&) = delete;
  TimeAnalyzer& operator=(const TimeAnalyzer&) = delete;

  std::chrono::microseconds GetMicroseconds() const;
  void Debug(const std::string& info) const;

 private:
  std::chrono::time_point<std::chrono::system_clock> time_initialized_;
};

}  // namespace helpers

#endif  // TIME_ANALYZER_H_
