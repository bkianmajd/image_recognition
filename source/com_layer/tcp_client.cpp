#include "com_layer/tcp_client.h"

#include <QHostAddress>

#include "com_layer/com_defs.h"

namespace com_layer {

TcpClient::TcpClient(QObject* parent)
    : QObject(parent),
      byte_array_(std::unique_ptr<QByteArray>(new QByteArray)),
      connected_(false) {
  // make a new socket
  socket_ = std::unique_ptr<QTcpSocket>(new QTcpSocket(this));

  connect(socket_.get(), SIGNAL(connected()), this, SLOT(OnConnected()));
  connect(socket_.get(), SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
  connect(socket_.get(), SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
}

void TcpClient::SetAndConnectSocket(int descriptor) {
  socket_->setSocketDescriptor(descriptor);
  socket_->connectToHost(QHostAddress(kConnectAddress), kPort);
}

void TcpClient::OnConnected() {
  qDebug() << "TCP CLient Connected!";
  connected_.store(true);
}

void TcpClient::OnDisconnected() { connected_.store(false); }

void TcpClient::OnReadyRead() {
  std::lock_guard<std::mutex> lock(byte_read_mutex_);
  byte_array_->append(socket_->readAll());
}

void TcpClient::SwapByteArray(QByteArray* byte_array) {
  std::lock_guard<std::mutex> lock(byte_read_mutex_);
  std::swap(*byte_array_, *byte_array);
}

bool TcpClient::Connected() { return connected_.load(); }

}  // namespace tcp_client
