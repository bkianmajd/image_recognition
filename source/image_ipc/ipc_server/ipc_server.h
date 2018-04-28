#ifndef IMAGE_IPC_IPC_SERVER_IPC_SERVER_H_
#define IMAGE_IPC_IPC_SERVER_IPC_SERVER_H_

#include <iostream>
#include <memory>

#include "com_layer/tcp_server.h"

namespace ipc_server {

/// @class IpcServer
/// This class wraps the tcp server and receives protobufs from the client.
/// It then converts the protobuf to a command struct and sends it to the
/// command handler.
/// The command handler will return a true or false. And the server will then
/// respond to the client with an ack or nack.
/// The IpcServerRunner runs CheckProtobuf at a fixedFrequency.
class IpcServer {
 public:
  // IpcServer(CommandHandlerInterface command_handler_interface_) {}
  IpcServer() {}

  /// Polls the tcp server for data
  void CheckPotobuf();

  /// Prints the status of the ipc server.
  void PrintStatus();

 private:
  com_layer::TcpServer tcp_server_;
};

}  // namespace ipc_server

#endif  // IMAGE_IPC_IPC_SERVER_IPC_SERVER_H_
