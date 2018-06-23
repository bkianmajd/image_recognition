#include "postal_service/com_layer/tcp_server.h"

#include <QHostAddress>
#include <iostream>

#include "postal_service/com_layer/com_defs.h"

namespace com_layer {

namespace {
constexpr int kMaxAcceptedData = 8192;
}  // namespace

TcpServer::TcpServer() : tcp_socket_(nullptr), byte_array_() {
  tcp_server_.setMaxPendingConnections(1);
  connect(&tcp_server_, SIGNAL(newConnection()), this, SLOT(OnNewConnection()));
}

TcpServer::~TcpServer() {
  tcp_server_.disconnect();
  if (tcp_socket_ == nullptr) {
    return;
  }
  if (tcp_socket_->isOpen()) {
    tcp_socket_->close();
  }
}

void TcpServer::Init() {
  if (!tcp_server_.listen(QHostAddress::Any, kPort)) {
    qDebug() << "Cannot listen";
    return;
  }
  qDebug() << "starting to listen!";
}

bool TcpServer::IsConnected() const {
  if(tcp_socket_ == nullptr) {
    return false;
  }
  return tcp_socket_->isOpen(); }

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
  byte_array_.append(tcp_socket_->readAll().toStdString());
  qDebug() << "Incoming message!";
}

void TcpServer::SwapReceivedByteArray(std::string& byte_array) {
  std::lock_guard<std::mutex> lock(byte_read_mutex_);
  std::swap(byte_array_, byte_array);
}

void TcpServer::SendData(const char* byte_array, int ln) const {
  tcp_socket_->write(byte_array, ln);
}

}  // namespace com_layer
