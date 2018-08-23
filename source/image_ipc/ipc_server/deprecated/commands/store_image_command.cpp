#include "store_image_command.h"

#include "image_ipc/ipc_server/responses/ack_response.h"

namespace ipc {
namespace ipc_server {

StoreImageCommand::StoreImageCommand(const uchar* data, int size,
                                     QImage::Format format,
                                     const std::string& file_name)
    : qformat_(format), qimage_(QImage::fromData(data, size, format)) {}

StoreImageCommand::~StoreImageCommand() {}

std::unique_ptr<IResponse> StoreImageCommand::ApplyCommand() {
  if (qimage_.save(file_name, qformat)) {
    return (std::unique_ptr<IResponse>(new AckResponse(true)));
  }
  return (std::unique_ptr<IResponse>(new AckResponse(false)));
}

}  // namespace ipc_server
}  // namespace ipc

#endif  // TEST_COMMAND_H_
