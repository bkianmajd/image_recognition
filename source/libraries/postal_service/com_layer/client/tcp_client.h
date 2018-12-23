#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include <QTcpSocket>
#include <QtGlobal>
#include <atomic>
#include <memory>
#include <mutex>

#include "gtest/gtest_prod.h"
#include "libraries/postal_service/com_layer/icarrier.h"

namespace com_layer {

class TcpClient : public QObject, public ICarrier {
  Q_OBJECT
 public:
  TcpClient(QObject* parent = nullptr);

  ~TcpClient() override;

  void Init(const ConnectionInfo& connection_info) override;

  bool IsConnected() const override;

  void SendData(const char* byte_array, int ln) override;

  void SwapReceivedByteArray(std::string& byte_array) override;

  void Disconnect() override;

 public slots:
  void OnConnected();
  void OnDisconnected();
  void OnReadyRead();

 signals:
  void ReadySend();

 private slots:
  void OnReadyRead();
  void OnReadySend();

 private:
  FRIEND_TEST(TcpClientTest, SwapByteArrayTest);

  std::unique_ptr<QTcpSocket> socket_;
  std::atomic_bool connected_;

  std::string byte_read_array_;
  std::mutex byte_read_mutex_;

  std::string byte_send_array_;
  std::mutex byte_send_mutex_;
};

}  // namespace tcp_client

#endif  // TCP_CLIENT_H_
