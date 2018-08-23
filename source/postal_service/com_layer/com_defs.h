#ifndef COM_LAYER_COM_DEFS_
#define COM_LAYER_COM_DEFS_

#include <QString>

namespace com_layer {

constexpr quint16 kDefaultPort = 8080;
const int kMaxBytes = 2048;
const QString kLocalHostAddress = "127.0.0.1";

struct ConnectionInfo {
  quint16 port = kDefaultPort;
  QString connection_address = kLocalHostAddress;
};

}  // namespace com_layer

#endif  // COM_LAYER_COM_DEFS_
