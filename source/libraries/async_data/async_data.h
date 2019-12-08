#ifndef ASYNC_DATA_H_
#define ASYNC_DATA_H_

#include <functional>
#include <mutex>

/// AsyncData alows a synchronization between a single data type.
template <typename T>
class AsyncData {
 public:
  AsyncData() = default;

  void Write(const T& t) {
    buffer0_ = t;

    // need to swap left to middle
    std::lock_guard<std::mutex> lg(buffer_swap_mutex_);
    std::swap(buffer0_, buffer1_);
    is_fresh_ = true;
  }

  void Write(const T&& t) {
    std::lock_guard<std::mutex> lg(buffer_swap_mutex_);
    std::swap(t, buffer1_);
    is_fresh_ = true;
  }

  T Read() {
    // needs to swap right to middle
    {
      std::lock_guard<std::mutex> lg(buffer_swap_mutex_);
      std::swap(buffer1_, buffer2_);
      is_fresh_ = false;
    }
    return buffer2_;
  }

  bool IsFresh() { return is_fresh_; }

 private:
  std::mutex buffer_swap_mutex_;

  T buffer0_;
  T buffer1_;
  T buffer2_;
  bool is_fresh_ = false;
};

#endif  // ASYNC_DATA_H_
