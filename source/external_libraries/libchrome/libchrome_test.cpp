#include <memory>

#include "gtest/gtest.h"

#include "base/callback.h"
// #include "base/threading/thread_checker.h"
#include "base/logging.h"
#include "base/message_loop/message_loop.h"

namespace libchrome {
namespace {
void SimpleCallback() {}
}

class LibchromeTest : public testing::Test {
 public:
  LibchromeTest() {}

 protected:
  // base::MessageLoop message_loop_;
};

TEST_F(LibchromeTest, ConstructDestruct) {}

TEST_F(LibchromeTest, Logging) {
  DCHECK(false);
  // CHECK_EQ(1,2);
  logging::LogMessage(__FILE__, __LINE__, logging::LOG_INFO);
}

TEST_F(LibchromeTest, CallbackForward) { base::Callback<void()> callback; }

TEST_F(LibchromeTest, MessageLoopTest) { base::MessageLoop message_loop; }

}  // namespace libchrome
