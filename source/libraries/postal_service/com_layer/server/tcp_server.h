#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "libraries/postal_service/com_layer/carrier_base.h"

#include <QTcpServer>

#include "gtest/gtest_prod.h"

namespace com_layer {

class TcpServer : public CarrierBase {
  Q_OBJECT
 public:
  TcpServer();

  virtual ~TcpServer() override;

  void Init(const ConnectionInfo& connection_info = ConnectionInfo()) override;

 protected:
  virtual void GiveUpTcpSocket(QTcpSocket* tcp_socket) override;

 private slots:
  void OnNewConnection();

 private:
  QTcpServer tcp_server_;
};

}  // namespace com_layer

#endif  // TCP_SERVER_H_
