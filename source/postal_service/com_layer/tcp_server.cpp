#include "postal_service/com_layer/tcp_server.h"

#include <QHostAddress>
#include <iostream>

#include "postal_service/com_layer/com_defs.h"

namespace com_layer {
namespace {

constexpr int kMaxAcceptedData = 8192;

}  // namespace

TcpServer::TcpServer() : tcp_socket_(nullptr), byte_read_array_() {
  byte_read_array_.clear();
  tcp_server_.setMaxPendingConnections(1);
  connect(&tcp_server_, SIGNAL(newConnection()), this, SLOT(OnNewConnection()));

  connect(this, SIGNAL(ReadySend()), this, SLOT(OnReadySend()));
}

TcpServer::~TcpServer() { Disconnect(); }

void TcpServer::Disconnect() {
  tcp_server_.close();
  if (tcp_socket_ == nullptr) {
    return;
  }
  if (tcp_socket_->isOpen()) {
    tcp_socket_->close();
  }
}

void TcpServer::Init(const ConnectionInfo& connection_info) {
  if (!tcp_server_.listen(QHostAddress::Any, connection_info.port)) {
    qDebug() << "Cannot listen";
    return;
  }
  qDebug() << "Starting to listen!";
}

bool TcpServer::IsConnected() const {
  if (tcp_socket_ == nullptr) {
    return false;
  }
  return tcp_socket_->isOpen();
}

void TcpServer::OnNewConnection() {
  qDebug() << "Tcp Server received new connection!\n";

  tcp_server_.pauseAccepting();
  tcp_socket_ = tcp_server_.nextPendingConnection();
  if (tcp_socket_ != nullptr) {
    connect(tcp_socket_, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
  }
}

void TcpServer::OnReadyRead() {
  std::lock_guard<std::mutex> lock(byte_read_mutex_);
  byte_read_array_.append(tcp_socket_->readAll().toStdString());
  qDebug() << "Incoming message! " << byte_read_array_.size();
}

void TcpServer::SwapReceivedByteArray(std::string& byte_array) {
  std::lock_guard<std::mutex> lock(byte_read_mutex_);
  if (byte_read_array_.empty()) {
    byte_array.clear();
    return;
  }
  std::swap(byte_read_array_, byte_array);
}

void TcpServer::SendData(const char* byte_array, int ln) {
  {
    std::lock_guard<std::mutex> lock(byte_write_mutex_);
    for (int i = 0; i < ln; ++i) {
      byte_write_array_.push_back(byte_array[i]);
    }
  }
  ReadySend();
}

void TcpServer::OnReadySend() {
  std::lock_guard<std::mutex> lock(byte_write_mutex_);
  tcp_socket_->write(byte_write_array_.c_str(), byte_write_array_.size());
  byte_write_array_.clear();
}

}  // namespace com_layer
