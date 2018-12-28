#ifndef CARRIER_MOCK_H_
#define CARRIER_MOCK_H_

#include "libraries/postal_service/com_layer/carrier_base.h"

#include <QTcpSocket>
#include <QtGlobal>
#include <cstdint>
#include <deque>
#include <memory>
#include <mutex>
#include <queue>

#include "libraries/postal_service/com_layer/com_defs.h"

namespace com_layer {

class CarrierMock : public CarrierBase {
 public:
  CarrierMock() = default;
  virtual ~CarrierMock() override = default;

  void Init(const ConnectionInfo& connection_info) override {
    (void)connection_info;
  }

 protected:
  void DoDisconnect() override {}
};

}  // namespace com_laer

#endif  // CARRIER_MOCK_H_
