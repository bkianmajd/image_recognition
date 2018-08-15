#ifndef IMAGE_COMMAND_DISTRIBUTOR_H_
#define IMAGE_COMMAND_DISTRIBUTOR_H_

#include "image_ipc/ipc_server/file_manager/file_manager.h"
#include "postal_service/imail_distributor.h"

namespace ipc {
namespace ipc_server {

class ImageCommandDistributor : public postal_service::IMailDistributor {
 public:
  ImageCommandDistributor(FileManager* file_manager);

  /// Postal service calls this to distribute a byte array
  /// this function therefore should decode the byte array and pass it up.
  /// This function decodes the string into ImageCommands and passes it up to
  /// respective managers.
  void Distribute(std::string& string) override;

 private:
  FileManager* file_manager_;
};

}  // namespace ipc
}  // namespace ipc_server

#endif  // IMAGE_COMMAND_DISTRIBUTOR_H_
