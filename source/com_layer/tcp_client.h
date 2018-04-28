#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include <QTcpSocket>
#include <QtGlobal>
#include <atomic>
#include <memory>
#include <mutex>

#include "gtest/gtest_prod.h"

namespace com_layer {

class TcpClient : public QObject {
  Q_OBJECT
 public:
  explicit TcpClient(QObject* parent = 0);

  void SetAndConnectSocket(int descriptor);

  void SwapByteArray(QByteArray* byte_array);

  bool Connected();

 public slots:
  void OnConnected();
  void OnDisconnected();
  void OnReadyRead();

 signals:

 private:
  FRIEND_TEST(TcpClientTest, SwapByteArrayTest);

  std::unique_ptr<QTcpSocket> socket_;
  std::unique_ptr<QByteArray> byte_array_;
  std::atomic_bool connected_;

  std::mutex byte_read_mutex_;
};

}  // namespace tcp_client

#endif  // TCP_CLIENT_H_
