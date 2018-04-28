#include "com_layer/tcp_server.h"

#include <QHostAddress>
#include <iostream>

#include "com_layer/com_defs.h"

namespace com_layer {

namespace {
constexpr int kMaxAcceptedData = 8192;
}  // namespace

TcpServer::TcpServer()
    : byte_array_(std::unique_ptr<QByteArray>(new QByteArray)) {
  tcp_server_.setMaxPendingConnections(1);
  connect(&tcp_server_, SIGNAL(newConnection()), this, SLOT(OnNewConnection()));
}

void TcpServer::StartListening() {
  if (!tcp_server_.listen(QHostAddress::Any, kPort)) {
    qDebug() << "Cannot listen";
    return;
  }
  qDebug() << "starting to listen!";
}

void TcpServer::OnNewConnection() {
  qDebug() << "Tcp Server received new connection!\n";

  tcp_server_.pauseAccepting();
  tcp_socket_ = tcp_server_.nextPendingConnection();
  if (tcp_socket_ != nullptr) {
    connect(tcp_socket_, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
  }
}

bool TcpServer::TcpIsOpen() const { return tcp_socket_->isOpen(); }

void TcpServer::OnReadyRead() {
  std::lock_guard<std::mutex> lock(byte_read_mutex_);
  byte_array_->append(tcp_socket_->readAll());
}

void TcpServer::SwapByteArray(QByteArray* byte_array) {
  std::lock_guard<std::mutex> lock(byte_read_mutex_);
  std::swap(*byte_array_, *byte_array);
}

}  // namespace com_layer
