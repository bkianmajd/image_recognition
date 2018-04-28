#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <QtGlobal>
#include <QTcpServer>
#include <QTcpSocket>
#include <mutex>
#include <memory>

#include "gtest/gtest_prod.h"

namespace com_layer {

class TcpServer : public QObject {
  Q_OBJECT
public:
  TcpServer();

  void StartListening();

  bool TcpIsOpen() const;

private slots:
  void OnNewConnection();

  // the |tcp_socket_| has sent a signal ReadyRead
  // and the tcp socket is ready to read data from the socket.
  void OnReadyRead();

  // Swap the |byte_array_|
  void SwapByteArray(QByteArray* byte_array);

private:
  FRIEND_TEST(TcpServerTest, SwapByteArrayTest);

  QTcpServer tcp_server_;
  QTcpSocket* tcp_socket_;
  std::unique_ptr<QByteArray> byte_array_;

  std::mutex byte_read_mutex_;
};

}  // namespace com_layer

#endif  // TCP_SERVER_H_
