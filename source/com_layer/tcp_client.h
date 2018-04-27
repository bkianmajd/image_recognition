#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include <QTcpSocket>
#include <QtGlobal>
#include <mutex>
#include <memory>

namespace com_layer {

class TcpClient : public QObject {
  Q_OBJECT
 public:
  explicit TcpClient(QObject *parent = 0);

  void SetSocket(int Descriptor);

 public slots:
  void OnConnected();
  void OnDisconnected();
  void OnReadyRead();

 signals:

 private:
  std::unique_ptr<QTcpSocket> socket_;
};

}  // namespace tcp_client

#endif  // TCP_CLIENT_H_
