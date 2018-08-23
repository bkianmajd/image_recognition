#ifndef ACK_RESPONSE_H_
#define ACK_RESPONSE_H_

#include "image_ipc/ipc_server/response_handler.h"
#include "schema/compiled_files/responses.pb.h"

namespace ipc {
namespace ipc_server {

class AckResponse : public IResponse {
 public:
  AckResponse(bool success) : success_(success) {}
  virtual ~AckResponse() {}

  google::protobuf::Any CreateProtobuf() override {
    response::AckResponse response;
    response.set_success(success_);

    // TODO(): Convert this to a util function
    google::protobuf::Any any;
    any.PackFrom(response);
    return any;
  }

 private:
  bool success_;
};

}  // ipc_server
}  // namespace ipc

#endif  // ACK_RESPONSE_H_
