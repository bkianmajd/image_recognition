#ifndef COM_LAYER_ICARRIER_H_
#define COM_LAYER_ICARRIER_H_

#include <QTcpSocket>
#include <QtGlobal>
#include <cstdint>
#include <deque>
#include <memory>
#include <mutex>
#include <queue>

#include "gtest/gtest_prod.h"
#include "libraries/postal_service/com_layer/com_defs.h"

namespace com_layer {

class CarrierBase : public QObject {
  Q_OBJECT
 public:
  CarrierBase();
  virtual ~CarrierBase();

  bool IsConnected() const;

  void Disconnect();

  void SendData(const char* byte_array, int ln);

  std::string ReadByteArray();

  virtual void Init(const ConnectionInfo& connection_info) = 0;

 signals:
  void ReadySend();

 protected:
  // This releases the tcp socket back to the child class
  virtual void GiveUpTcpSocket(QTcpSocket* tcp_socket) = 0;

  // The child class calls into this function to set the TCP socket
  void ConsumeTcpSocket(QTcpSocket* tcp_socket);

 private slots:
  void OnReadyRead();

  void OnReadySend();

 private:
  friend class CarrierTest;
  FRIEND_TEST(CarrierTest, ReadByteArrayTest);

  void ProcessReadBytes(const QByteArray& array);

  void StoreByteQueueIntoPacket();

  bool CheckForPacketEnd(char a);

  const std::string kEndPacket;

  std::size_t end_of_packet_index_;

  QTcpSocket* socket_;
  std::deque<char> byte_read_queue_;

  std::queue<std::string> incoming_packets_;
  std::mutex byte_read_mutex_;

  std::string byte_write_array_;
  std::mutex byte_write_mutex_;
};

}  // namespace com_laer

#endif  // COM_LAYER_ICARIER_H_
