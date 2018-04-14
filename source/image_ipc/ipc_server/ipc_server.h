#ifndef RPC_IMAGE_RPC_SERVER_RPC_SERVER_H_
#define RPC_IMAGE_RPC_SERVER_RPC_SERVER_H_

#include <iostream>

#include "schema/compiled_files/template_match.grpc.pb.h"
#include "external_libraries/googletest/include/gtest/gtest_prod.h"

namespace rpc_server {

class RpcServer : public ImageRecognitionRpc::Service {
public:
  RpcServer() {}

  ::grpc::Status PostImageRequest(::grpc::ClientContext* context,
                                  const ::ImageRequest& request,
                                  ::ImageResponse* response) {
    response->set_success(true);
    return ::grpc::Status::OK;
  }

private:

};

}  // namespace rpc_server

#endif  // RPC_IMAGE_RPC_SERVER_RPC_SERVER_H_
