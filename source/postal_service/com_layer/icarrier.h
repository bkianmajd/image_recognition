#ifndef COM_LAYER_ICARRIER_H_
#define COM_LAYER_ICARRIER_H_

#include <cstdint>

namespace com_layer {

class ICarrier {
public:
  virtual ~ICarrier() {}
  virtual void SendData(const char* byte_array, int ln) const = 0;
  virtual void SwapReceivedByteArray(std::string& byte_array) = 0;
};

}  // namespace com_laer

#endif  // COM_LAYER_ICARIER_H_
