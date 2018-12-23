#ifndef COM_LAYER_ICARRIER_H_
#define COM_LAYER_ICARRIER_H_

#include <QTcpSocket>
#include <cstdint>
#include <deque>
#include <memory>
#include <mutex>
#include <queue>

#include "libraries/postal_service/com_layer/com_defs.h"

namespace com_layer {
namespace {
const std::string kPacketEndNotifier = "PACKET_END_Notifier";
const size_t kEndSize = kPacketEndNotifier.size();
}  // namespace

class CarrierBase : public QObject {
 public:
  CarrierBase() {}
  virtual ~CarrierBase() {}

  bool IsConnected() const { return socket_->isOpen(); }

  void Disconnect() {
    DoDisconnect();
    if (socket_ == nullptr) {
      return;
    }
    if (socket_->isOpen()) {
      socket_->close();
    }
  }

  void SendData(const char* byte_array, int ln) {
    std::lock_guard<std::mutex> lock(byte_write_mutex_);
    for (int i = 0; i < ln; ++i) {
      byte_write_array_.push_back(byte_array[i]);
    }
    for (char a : kPacketEndNotifier) {
      byte_write_array_.push_back(a);
    }
    ReadySend();
  }

  std::string ReadByteArray() {
    std::lock_guard<std::mutex> lock(byte_read_mutex_);

    if (incoming_packets_.empty()) {
      return std::string();
    }

    std::string packet = incoming_packets_.front();
    incoming_packets_.pop();
    return packet;
  }

  virtual void Init(const ConnectionInfo& connection_info) = 0;

 protected:
  virtual void DoDisconnect() = 0;
  // The child class calls into this function to set the TCP socket
  void SetTcpSocket(std::unique_ptr<QTcpSocket>&& tcp_socket) {
    socket_ = std::move(tcp_socket);
  }

 private slots:
  void OnReadyRead() {
    QByteArray byte_array = socket_->readAll();
    qDebug() << "Incoming message! " << byte_array.size();

    // Push the byte_array in the dequeue
    for (char a : byte_array) {
      byte_read_queue_.push_back(a);
      if (CheckForPacketEnd(a)) {
        StoreByteQueueIntoPacket();
      }
    }
  }

  void OnReadySend() {
    std::lock_guard<std::mutex> lock(byte_write_mutex_);
    socket_->write(byte_write_array_.c_str(),
                   static_cast<int64_t>(byte_write_array_.size()));
    byte_write_array_.clear();
  }

 signals:
  void ReadySend();

 private:
  void StoreByteQueueIntoPacket() {
    // First remove the end packet
    for (std::size_t i = 0; i < kEndSize; ++i) {
      byte_read_queue_.pop_back();
    }
    std::string packet(byte_read_queue_.begin(), byte_read_queue_.end());

    std::lock_guard<std::mutex> lock(byte_read_mutex_);
    incoming_packets_.push(std::move(packet));
  }

  bool CheckForPacketEnd(char a) {
    if (kPacketEndNotifier[end_of_packet_index_] != a) {
      end_of_packet_index_ = 0;
      return false;
    }
    // The char has matched the index in the string
    end_of_packet_index_++;

    // end of packet index should always be less than size
    if (end_of_packet_index_ < kEndSize) {
      return false;
    }

    // Else the packet has ended
    end_of_packet_index_ = 0;
    return true;
  }

  std::size_t end_of_packet_index_;

  std::unique_ptr<QTcpSocket> socket_;
  std::deque<char> byte_read_queue_;

  std::queue<std::string> incoming_packets_;
  std::mutex byte_read_mutex_;

  std::string byte_write_array_;
  std::mutex byte_write_mutex_;
};

}  // namespace com_laer

#endif  // COM_LAYER_ICARIER_H_
