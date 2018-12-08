#ifndef IPC_CLIENT_H_
#define IPC_CLIENT_H_

#include "postal_service/postal_service.h"
#include "postal_service/utility/mail_distributor_queue.h"
#include "postal_service/utility/post_card_queue.h"
#include "schema/compiled_files/image_request_response_commands.pb.h"

struct Point {
  int x;
  int y;
};

class IpcClient {
 public:
  // Must be instantiated from qt main
  IpcClient(com_layer::ConnectionInfo connection_info)
      : client_(postal_service::client) {}

  // Send the binary - blocking clal
  bool StoreImage(const std::string& image_name,
                  const std::string& abs_path_image) {
    // Get the binary of the file image
    std::vector<char> binary = file_manager.ReadFile(
        directory_finder.GetAbsPathOfTargetFile(abs_path_image));
    if (binary.size() == 0) {
      std::cerr << "couldn't find image" << std::endl;
      return false;
    }

    // Call the proto file image_reqeuest_response_commands
    std::unique_ptr<ipc_interface::StoreImageRequest> request =
        std::make_unique<ipc_interface::StoreImageRequest>();
    std::string* str = request->mutable_image();
    str->append(binary.begin(), binary.end());
    request->mutable_image_name()->append(image_name.c_str());
    if (request->ByteSize() == 0) {
      std::cerr << "couldn't generate protobuf" << std::endl;
      return false;
    }

    post_card_queue_.Push(std::move(request));

    // Wait for the response
    // TODO : put timeout
    while (response_queue_.Empty()) {
      client_.GetMail(response_queue);
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    const google::protobuf::Any& test = response_queue_.Front();

    return true;
  }

  bool TemplateMatch(const std::string& big_image,
                     const std::string& template_image, Point* point);

 private:
  postal_service::PostalService client_;
  postal_service::PostCardQueue post_card_queue_;
  postal_service::MailDistributorQueue response_queue_;
};

#endif  // IPC_CLIENT_H_
