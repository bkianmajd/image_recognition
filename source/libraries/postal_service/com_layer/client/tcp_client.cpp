#include "libraries/postal_service/com_layer/client/tcp_client.h"

#include <QHostAddress>
#include <iostream>

#include "libraries/postal_service/com_layer/com_defs.h"

namespace com_layer {

TcpClient::TcpClient() {}

TcpClient::~TcpClient() {}

void TcpClient::Init(const ConnectionInfo& connection_info) {
  qDebug() << "Attempting to connect to host";

  // make a new socket
  socket_ = new QTcpSocket(this);
  connect(socket_, SIGNAL(connected()), this, SLOT(OnConnected()));

  socket_->setSocketDescriptor(connection_info.port);
  socket_->connectToHost(
      QHostAddress(connection_info.connection_address.c_str()),
      static_cast<std::uint16_t>(connection_info.port));
}

void TcpClient::OnConnected() {
  qDebug() << "TCP CLient Connected!";
  CarrierBase::ConsumeTcpSocket(socket_);
  socket_ = nullptr;
}

void TcpClient::GiveUpTcpSocket(QTcpSocket* socket) {
  if(socket!= nullptr) {
    delete socket;
  }
}

}  // namespace tcp_client
