#include "components/image_service/client/ipc_client.h"

#include <thread>

namespace ipc {

// Must be instantiated from qt main
IpcClient::IpcClient(com_layer::ConnectionInfo connection_info)
    : client_(postal_service::client), response_queue_() {}

// Send the binary - blocking clal
bool IpcClient::SendImage(const std::vector<char>& binary,
                          const std::string& image_name) {
  // Get the binary of the file image
  if (binary.size() == 0) {
    std::cerr << "couldn't find image" << std::endl;
    return false;
  }

  // Call the proto file image_reqeuest_response_commands
  ipc_interface::StoreImageRequest request;
  std::string* str = request.mutable_image();
  str->append(binary.begin(), binary.end());
  request.mutable_image_name()->append(image_name.c_str());
  if (request.ByteSize() == 0) {
    std::cerr << "couldn't generate protobuf" << std::endl;
    return false;
  }

  client_.SendMail(request);

  // Wait for the response
  // TODO : put timeout
  while (response_queue_.Empty()) {
    client_.GetMail(response_queue_);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  const google::protobuf::Any& any_message = response_queue_.Front();

  ipc_interface::StoreImageResponse response;
  if (any_message.Is<ipc_interface::StoreImageResponse>()) {
    any_message.UnpackTo(&response);
  }

  if (!response.success()) {
    std::cerr << response.str_message() << std::endl;
  }

  return true;
}

}  // namespace ipc
