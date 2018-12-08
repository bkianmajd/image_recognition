#ifndef COM_LAYER_COM_DEFS_
#define COM_LAYER_COM_DEFS_

#include <string>

namespace com_layer {

constexpr int kDefaultPort = 8080;
constexpr int kMaxBytes = 2048;
constexpr char kLocalHostAddress[] = "127.0.0.1";

struct ConnectionInfo {
  int port = kDefaultPort;
  std::string connection_address = kLocalHostAddress;
};

}  // namespace com_layer

#endif  // COM_LAYER_COM_DEFS_
