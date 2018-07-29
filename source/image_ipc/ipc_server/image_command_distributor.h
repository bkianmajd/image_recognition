#ifndef IMAGE_COMMAND_DISTRIBUTOR_H_
#define IMAGE_COMMAND_DISTRIBUTOR_H_

#include "image_ipc/ipc_server/icommand.h"
#include "postal_service/imail_distributor.h"

namespace ipc {
namespace ipc_server {

class ImageCommandDistributor : public postal_service::IMailDistributor {
 public:
  ImageCommandDistributor() {}

  /// Postal service calls this to distribute a byte array
  /// this function therefore should decode the byte array and pass it up
  void Distribute(std::string& string) override;

 private:
  std::unique_ptr<ICommand> FindICommand(std::string& string) const;
};

}  // namespace ipc
}  // namespace ipc_server

#endif  // IMAGE_COMMAND_DISTRIBUTOR_H_
