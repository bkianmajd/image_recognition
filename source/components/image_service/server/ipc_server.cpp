#include "components/image_service/server/ipc_server.h"

namespace ipc {
IpcServer::IpcServer() : server_(postal_service::Type::server) {}

void IpcServer::AsyncInit(const com_layer::ConnectionInfo& connection_info) {
  server_.AsyncInit(connection_info);
}

bool IpcServer::IsInit() { return server_.IsOpen(); }

bool IpcServer::CheckForImage(int* client_identifier,
                              std::vector<char>* bytes) {
  if (!server_.IsOpen()) {
    return false;
  }

  // Gets the mail from the qt socket and signals
  server_.GetMail(request_queue_);

  // Mail is empty for now
  if (request_queue_.Empty()) {
    return true;
  }

  // Process the request queue
  const google::protobuf::Any& any_message = request_queue_.Front();
  ipc_interface::StoreImageRequest request;
  if (!any_message.Is<ipc_interface::StoreImageRequest>()) {
    std::cerr << "Unknown any message command" << std::endl;
    request_queue_.Pop();
    return false;
  }

  // Success in peeling from the queue
  any_message.UnpackTo(&request);
  request_queue_.Pop();

  SendAcknowledgement();

  // Copying the string into a vector of char
  std::vector<char> raw_bytes(request.image().begin(), request.image().end());
  std::swap(*bytes, raw_bytes);

  return true;
}

void IpcServer::SendAcknowledgement() {
  ipc_interface::StoreImageResponse response;
  response.set_success(true);
  server_.SendMail(response);
}

}  // namespace ipc
