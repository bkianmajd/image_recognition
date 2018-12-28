#include "libraries/postal_service/com_layer/server/tcp_server.h"

#include <QHostAddress>
#include <cstdint>
#include <iostream>

#include "libraries/postal_service/com_layer/com_defs.h"

namespace com_layer {
namespace {}  // namespace

TcpServer::TcpServer() {
  tcp_server_.setMaxPendingConnections(1);
  connect(&tcp_server_, SIGNAL(newConnection()), this, SLOT(OnNewConnection()));
}

TcpServer::~TcpServer() { tcp_server_.close(); }

void TcpServer::Init(const ConnectionInfo& connection_info) {
  if (!tcp_server_.listen(QHostAddress::Any,
                          static_cast<std::uint16_t>(connection_info.port))) {
    qDebug() << "Cannot listen";
    return;
  }
  qDebug() << "Starting to listen!";
}

void TcpServer::GiveUpTcpSocket(QTcpSocket* tcp_socket) { delete tcp_socket; }

void TcpServer::OnNewConnection() {
  qDebug() << "Tcp Server received new connection!\n";

  tcp_server_.pauseAccepting();
  QTcpSocket* tcp_socket = tcp_server_.nextPendingConnection();
  if (tcp_socket != nullptr) {
    CarrierBase::ConsumeTcpSocket(tcp_socket);
  }
}

}  // namespace com_layer
