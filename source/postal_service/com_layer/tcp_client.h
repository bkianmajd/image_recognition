#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include <QTcpSocket>
#include <QtGlobal>
#include <atomic>
#include <memory>
#include <mutex>

#include "gtest/gtest_prod.h"
#include "postal_service/com_layer/icarrier.h"

namespace com_layer {

class TcpClient : public QObject, public ICarrier {
  Q_OBJECT
 public:
  explicit TcpClient(QObject* parent = 0);

  ~TcpClient() override;

  void Init() override;

  bool IsConnected() const override;

  void SendData(const char* byte_array, int ln) const override;

  void SwapReceivedByteArray(std::string& byte_array) override;

 public slots:
  void OnConnected();
  void OnDisconnected();
  void OnReadyRead();

 signals:

 private:
  FRIEND_TEST(TcpClientTest, SwapByteArrayTest);

  std::unique_ptr<QTcpSocket> socket_;
  std::atomic_bool connected_;

  std::string byte_array_;
  std::mutex byte_read_mutex_;
};

}  // namespace tcp_client

#endif  // TCP_CLIENT_H_
