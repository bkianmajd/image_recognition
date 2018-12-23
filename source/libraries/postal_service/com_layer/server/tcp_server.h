#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <QTcpServer>
#include <QTcpSocket>
#include <QtGlobal>
#include <memory>
#include <mutex>

#include "gtest/gtest_prod.h"
#include "libraries/postal_service/com_layer/icarrier.h"

namespace com_layer {

class TcpServer : public QObject, public ICarrier {
  Q_OBJECT
 public:
  TcpServer();

  ~TcpServer();

  void Init(const ConnectionInfo& connection_info = ConnectionInfo()) override;

  // TcpIsOpen
  bool IsConnected() const override;

  // Send the byte array
  void SendData(const char* byte_array, int ln);

  // Swap the |byte_array_|
  void SwapReceivedByteArray(std::string& byte_array) override;

  void Disconnect() override;

 signals:
  void ReadySend();

 private slots:
  void OnNewConnection();

  // the |tcp_socket_| has sent a signal ReadyRead
  // and the tcp socket is ready to read data from the socket.
  void OnReadyRead();
  void OnReadySend();

 private:
  FRIEND_TEST(TcpServerTest, SwapByteArrayTest);

  QTcpServer tcp_server_;
  QTcpSocket* tcp_socket_;

  std::string byte_read_array_;
  std::mutex byte_read_mutex_;

  std::string byte_write_array_;
  std::mutex byte_write_mutex_;
};

}  // namespace com_layer

#endif  // TCP_SERVER_H_
