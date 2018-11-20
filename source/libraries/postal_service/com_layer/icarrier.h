#ifndef COM_LAYER_ICARRIER_H_
#define COM_LAYER_ICARRIER_H_

#include <cstdint>
#include "libraries/postal_service/com_layer/com_defs.h"

namespace com_layer {

class ICarrier {
 public:
  virtual ~ICarrier() {}
  virtual bool IsConnected() const = 0;
  virtual void SendData(const char* byte_array, int ln) = 0;
  virtual void SwapReceivedByteArray(std::string& byte_array) = 0;
  virtual void Init(const ConnectionInfo& connection_info) = 0;
  virtual void Disconnect() = 0;
};

}  // namespace com_laer

#endif  // COM_LAYER_ICARIER_H_
