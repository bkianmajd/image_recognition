#ifndef SESSION_THREAD_H_
#define SESSION_THREAD_H_

#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include <base/bind.h>
#include <base/memory/scoped_refptr.h>
#include <base/message_loop/message_loop.h>
#include <base/optional.h>
#include <base/single_thread_task_runner.h>
#include <base/task_runner.h>

/// SessionThread allows for a single class to run on a message loop
template <typename T>
class SessionThread {
 public:
  SessionThread() = default;

  ~SessionThread() {
    if (thread_.has_value()) {
      EndSessionAndJoin();
    }
  }

  /// Concrete T allows polymoprhism if T is the base class
  template <typename Concrete_T, typename... Args>
  bool StartSession(Args&&... args) {
    if (thread_.has_value()) {
      std::cerr << "thread is in session" << std::endl;
      return false;
    }
    thread_ = std::thread(&SessionThread::Session<Concrete_T, Args&...>, this,
                          std::forward<Args>(args)...);
    assert(thread_.has_value());

    // Edge case when thread starts and immediately is called close
    while (session_ == nullptr) {
      base::PlatformThread::Sleep(base::TimeDelta::FromMicroseconds(50));
    }

    return true;
  }

  bool EndSessionAndJoin() {
    if (!thread_.has_value()) {
      std::cerr << "thread has not started" << std::endl;
      return false;
    }

    task_runner_->PostTask(FROM_HERE, closure_);

    // Reset thread state
    thread_->join();
    thread_.reset();
    task_runner_.reset();
    closure_.Reset();
    return true;
  }

  scoped_refptr<base::SingleThreadTaskRunner> task_runner() const {
    return task_runner_;
  }

  T* get() const { return session_.get(); }

 private:
  template <typename Concrete_T, typename... Args>
  void Session(Args&&... args) {
    base::MessageLoop message_loop;
    base::RunLoop run_loop;
    closure_ = run_loop.QuitClosure();
    task_runner_ = message_loop.task_runner();

    // Start the session
    session_ = std::make_unique<Concrete_T>(std::forward<Args>(args)...);

    run_loop.Run();

    // Destruct the object
    session_.reset();
  }

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  base::Closure closure_;
  base::Optional<std::thread> thread_;
  std::unique_ptr<T> session_;
};

#endif  // SESSION_THREAD_H_
