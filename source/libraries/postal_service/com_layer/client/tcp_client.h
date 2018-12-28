#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include "libraries/postal_service/com_layer/carrier_base.h"

#include <QTcpSocket>
#include <QtGlobal>
#include <atomic>
#include <memory>
#include <mutex>

#include "gtest/gtest_prod.h"

namespace com_layer {

class TcpClient : public CarrierBase {
  Q_OBJECT
 public:
  TcpClient();

  virtual ~TcpClient() override;

  void Init(const ConnectionInfo& connection_info = ConnectionInfo()) override;

 protected:
  virtual void GiveUpTcpSocket(QTcpSocket* socket) override;

private slots:
 void OnConnected();

private:
 QTcpSocket* socket_;
};

}  // namespace tcp_client

#endif  // TCP_CLIENT_H_
