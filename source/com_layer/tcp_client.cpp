#include "com_layer/tcp_client.h"

#include <QHostAddress>

#include "com_layer/com_defs.h"

namespace com_layer {

TcpClient::TcpClient(QObject *parent) : QObject(parent) {}

void TcpClient::SetSocket(int Descriptor) {
  // make a new socket
  socket_ = std::unique_ptr<QTcpSocket>(new QTcpSocket(this));

  // qDebug() << "A new socket created!";
  connect(socket_.get(), SIGNAL(connected()), this, SLOT(OnConnected()));
  connect(socket_.get(), SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
  connect(socket_.get(), SIGNAL(readyRead()), this, SLOT(OnReadyRead()));

  socket_->setSocketDescriptor(Descriptor);

  socket_->connectToHost(QHostAddress::LocalHost, kPort);
}

void TcpClient::OnConnected() { qDebug() << "Client connected event"; }

void TcpClient::OnDisconnected() { qDebug() << "Disconnected event"; }

void TcpClient::OnReadyRead() { qDebug() << "On read event"; }

}  // namespace tcp_client
