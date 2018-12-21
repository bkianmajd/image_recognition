namespace ipc_server {

constexpr int kPort = 8080;
// const char* kConnectionAddress = "123.123.123";
const char* kConnectionAddress = "127.0.0.1";
const std::chrono::seconds kTimeout = std::chrono::seconds(60);

}  // ipc_server
