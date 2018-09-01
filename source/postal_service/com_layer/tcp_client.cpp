#include "postal_service/com_layer/tcp_client.h"

#include <QHostAddress>
#include <iostream>

#include "postal_service/com_layer/com_defs.h"

namespace com_layer {

TcpClient::TcpClient(QObject* parent) : QObject(parent), connected_(false) {
  // make a new socket
  socket_ = std::unique_ptr<QTcpSocket>(new QTcpSocket(this));

  connect(socket_.get(), SIGNAL(connected()), this, SLOT(OnConnected()));
  connect(socket_.get(), SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
  connect(socket_.get(), SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
  connect(this, SIGNAL(ReadySend()), this, SLOT(OnReadySend()));
}

TcpClient::~TcpClient() { Disconnect(); }

void TcpClient::Disconnect() { socket_->close(); }

void TcpClient::Init(const ConnectionInfo& connection_info) {
  qDebug() << "Attempting to connect to host";
  socket_->setSocketDescriptor(connection_info.port);
  socket_->connectToHost(
      QHostAddress(connection_info.connection_address.c_str()),
      connection_info.port);
}

bool TcpClient::IsConnected() const { return connected_.load(); }

void TcpClient::OnConnected() {
  qDebug() << "TCP CLient Connected!";
  connected_.store(true);
}

void TcpClient::OnDisconnected() { connected_.store(false); }

void TcpClient::OnReadyRead() {
  std::lock_guard<std::mutex> lock(byte_read_mutex_);
  QByteArray array = socket_->readAll();
  for (int i = 0; i < array.size(); ++i) {
    byte_read_array_.push_back(array.at(i));
  }
}

void TcpClient::SwapReceivedByteArray(std::string& byte_array) {
  std::lock_guard<std::mutex> lock(byte_read_mutex_);
  std::swap(byte_read_array_, byte_array);
}

void TcpClient::SendData(const char* byte_array, int ln) {
  {
    std::lock_guard<std::mutex> lock(byte_send_mutex_);
    for (int i = 0; i < ln; ++i) {
      byte_send_array_.push_back(byte_array[i]);
    }
  }
  ReadySend();
}

void TcpClient::OnReadySend() {
  std::lock_guard<std::mutex> lock(byte_send_mutex_);
  socket_->write(byte_send_array_.c_str(), byte_send_array_.size());
  byte_send_array_.clear();
}

}  // namespace tcp_client
