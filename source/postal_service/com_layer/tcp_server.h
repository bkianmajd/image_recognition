#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <QTcpServer>
#include <QTcpSocket>
#include <QtGlobal>
#include <memory>
#include <mutex>

#include "gtest/gtest_prod.h"
#include "postal_service/com_layer/icarrier.h"

namespace com_layer {

class TcpServer : public QObject, public ICarrier {
  Q_OBJECT
 public:
  TcpServer();

  ~TcpServer();

  void Init() override;

  // TcpIsOpen
  bool IsConnected() const override;

  // Send the byte array
  void SendData(const char* byte_array, int ln) const override;

  // Swap the |byte_array_|
  void SwapReceivedByteArray(std::string& byte_array) override;

 private slots:
  void OnNewConnection();

  // the |tcp_socket_| has sent a signal ReadyRead
  // and the tcp socket is ready to read data from the socket.
  void OnReadyRead();

 private:
  FRIEND_TEST(TcpServerTest, SwapByteArrayTest);

  QTcpServer tcp_server_;
  QTcpSocket* tcp_socket_;
  std::string byte_array_;

  std::mutex byte_read_mutex_;
};

}  // namespace com_layer

#endif  // TCP_SERVER_H_
