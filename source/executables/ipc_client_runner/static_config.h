#include <chrono>

namespace ipc_client {

constexpr int kPort = 8080;
constexpr char kConnectionAddress[] = "192.168.86.24";
// constexpr char kConnectionAddress[] = "127.0.0.1";
const std::chrono::seconds kTimeout = std::chrono::seconds(5);

}  // ipc_client
