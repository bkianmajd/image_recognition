#ifndef STORE_IMAGE_COMMAND_H_
#define STORE_IMAGE_COMMAND_H_

#include <QImage>
#include <iostream>
#include <memory>
#include "image_ipc/ipc_server/icommand.h"
#include "image_ipc/ipc_server/iresponse.h"

namespace ipc {
namespace ipc_server {

class StoreImageCommand : public ICommand {
 public:
  // QImage::Format_RGB16
  StoreImageCommand(const uchar* data, int size, QImage::Format format,
                    const std::string& file_name);

  virtual ~StoreImageCommand();

  std::unique_ptr<IResponse> ApplyCommand() override;

 private:
  QImage::Format qformat_;
  QImage qimage_;
};

}  // namespace ipc_server
}  // namespace ipc

#endif  // STORE_IMAGE_COMMAND_H_
