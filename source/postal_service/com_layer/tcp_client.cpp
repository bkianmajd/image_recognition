#include "postal_service/com_layer/tcp_client.h"

#include <QHostAddress>

#include "postal_service/com_layer/com_defs.h"

namespace com_layer {

TcpClient::TcpClient(QObject* parent) : QObject(parent), connected_(false) {
  // make a new socket
  socket_ = std::unique_ptr<QTcpSocket>(new QTcpSocket(this));

  connect(socket_.get(), SIGNAL(connected()), this, SLOT(OnConnected()));
  connect(socket_.get(), SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
  connect(socket_.get(), SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
}

TcpClient::~TcpClient() {
  socket_->close();
}

void TcpClient::Init() {
  qDebug() << "Attempting to connect to host";
  socket_->setSocketDescriptor(kPort);
  socket_->connectToHost(QHostAddress(kConnectAddress), kPort);
}

void TcpClient::OnConnected() {
  qDebug() << "TCP CLient Connected!";
  connected_.store(true);
}

void TcpClient::OnDisconnected() { connected_.store(false); }

void TcpClient::OnReadyRead() {
  std::lock_guard<std::mutex> lock(byte_read_mutex_);
  byte_array_.append(socket_->readAll());
}

void TcpClient::SwapReceivedByteArray(std::string& byte_array) {
  std::lock_guard<std::mutex> lock(byte_read_mutex_);
  std::swap(byte_array_, byte_array);
}

void TcpClient::SendData(const char* byte_array, int ln) const {
  socket_->write(byte_array, ln);
}

bool TcpClient::Connected() { return connected_.load(); }

}  // namespace tcp_client
