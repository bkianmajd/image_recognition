#include <chrono>

namespace ipc_client {

constexpr int kPort = 8080;
// const char* kConnectionAddress = "123.123.123";
constexpr char kConnectionAddress[] = "127.0.0.1";
const std::chrono::seconds kTimeout = std::chrono::seconds(5);

}  // ipc_client
