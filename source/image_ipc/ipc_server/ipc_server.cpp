#include "image_ipc/ipc_server/ipc_server.h"

#include <iostream>

namespace ipc_server {

namespace {}  // namespace

void IpcServer::CheckPotobuf() { std::unique_ptr<QByteArray> qByte_(new QByteArray); }

void IpcServer::PrintStatus() {
  std::cout << "TCP is open: " << tcp_server_.TcpIsOpen() << std::endl;
}

}  // namespace ipc_server
