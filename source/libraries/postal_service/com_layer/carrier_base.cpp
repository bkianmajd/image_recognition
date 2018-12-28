#include "libraries/postal_service/com_layer/carrier_base.h"

#include <cstdint>

#include "libraries/postal_service/com_layer/com_defs.h"

namespace com_layer {
namespace {
const std::string kPacketEndNotifier = "PACKET_END_Notifier";
const size_t kEndSize = kPacketEndNotifier.size();
}  // namespace

CarrierBase::CarrierBase() : kEndPacket(kPacketEndNotifier), socket_(nullptr) {
  connect(this, SIGNAL(ReadySend()), this, SLOT(OnReadySend()));
}

CarrierBase::~CarrierBase() {
  if (socket_ == nullptr) {
    return;
  }
  if (socket_->isOpen()) {
    socket_->close();
  }
}

bool CarrierBase::IsConnected() const { return socket_->isOpen(); }

void CarrierBase::Disconnect() {
  if (socket_ == nullptr) {
    return;
  }
  if (socket_->isOpen()) {
    socket_->close();
  }
  GiveUpTcpSocket(socket_);
}

void CarrierBase::SendData(const char* byte_array, int ln) {
  std::lock_guard<std::mutex> lock(byte_write_mutex_);
  for (int i = 0; i < ln; ++i) {
    byte_write_array_.push_back(byte_array[i]);
  }
  for (char a : kEndPacket) {
    byte_write_array_.push_back(a);
  }
  ReadySend();
}

std::string CarrierBase::ReadByteArray() {
  std::lock_guard<std::mutex> lock(byte_read_mutex_);

  if (incoming_packets_.empty()) {
    return std::string();
  }

  std::string packet = incoming_packets_.front();
  incoming_packets_.pop();
  return packet;
}

void CarrierBase::ConsumeTcpSocket(QTcpSocket* tcp_socket) {
  std::lock_guard<std::mutex> g1(byte_read_mutex_);
  std::lock_guard<std::mutex> g2(byte_write_mutex_);

  if (socket_ != nullptr) {
    GiveUpTcpSocket(socket_);
  }
  socket_ = tcp_socket;
  connect(socket_, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
}

void CarrierBase::OnReadyRead() {
  if (socket_ == nullptr) {
    return;
  }
  QByteArray byte_array = socket_->readAll();
  qDebug() << "Incoming message! " << byte_array.size();

  ProcessReadBytes(byte_array);
}

void CarrierBase::ProcessReadBytes(const QByteArray& array) {
  // Push the byte_array in the dequeue
  for (char a : array) {
    byte_read_queue_.push_back(a);
    if (CheckForPacketEnd(a)) {
      StoreByteQueueIntoPacket();
    }
  }
}

void CarrierBase::OnReadySend() {
  std::lock_guard<std::mutex> lock(byte_write_mutex_);
  socket_->write(byte_write_array_.c_str(),
                 static_cast<int64_t>(byte_write_array_.size()));
  byte_write_array_.clear();
}

void CarrierBase::StoreByteQueueIntoPacket() {
  // First remove the end packet
  for (std::size_t i = 0; i < kEndSize; ++i) {
    byte_read_queue_.pop_back();
  }
  std::string packet(byte_read_queue_.begin(), byte_read_queue_.end());

  std::lock_guard<std::mutex> lock(byte_read_mutex_);
  incoming_packets_.push(std::move(packet));
}

bool CarrierBase::CheckForPacketEnd(char a) {
  if (kEndPacket[end_of_packet_index_] != a) {
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

}  // namespace com_laer
