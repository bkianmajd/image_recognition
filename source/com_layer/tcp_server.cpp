#include "com_layer/tcp_server.h"

#include <QHostAddress>
#include <iostream>

#include "com_layer/com_defs.h"

namespace com_layer {

namespace {
constexpr int kMaxAcceptedData = 8192;
}  // namespace

TcpServer::TcpServer() {
  tcp_server_.setMaxPendingConnections(1);
  connect(&tcp_server_, SIGNAL(newConnection()), this, SLOT(OnNewConnection()));
}

void TcpServer::StartListening() {
  if (!tcp_server_.listen(QHostAddress::Any, kPort)) {
    qDebug() << "Cannot listen";
    return;
  }
  qDebug() << "starting to listen";
}

void TcpServer::OnNewConnection() {
  qDebug() << "New connection\n";

  tcp_server_.pauseAccepting();
  tcp_socket_ = tcp_server_.nextPendingConnection();
  if (tcp_socket_ != nullptr) {
    connect(tcp_socket_, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
  }
}

void TcpServer::OnReadyRead() {
  // byte_array_.append(tcp_socket_->read());
  // std::cout << "size: " << byte_array_.size() << std::endl;
}

}  // namespace com_layer
