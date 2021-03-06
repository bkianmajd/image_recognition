#include "libraries/postal_service/postal_service.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "external_libraries/protobuf-3.5.x/src/google/protobuf/any.pb.h"
#include "libraries/postal_service/com_layer/client/tcp_client.h"
#include "libraries/postal_service/com_layer/com_defs.h"
#include "libraries/postal_service/com_layer/server/tcp_server.h"

namespace postal_service {
namespace {

constexpr std::chrono::seconds kInitTimeout = std::chrono::seconds(60);

std::unique_ptr<com_layer::CarrierBase> CarrierFactory(Type type) {
  if (type == Type::server) {
    return std::unique_ptr<com_layer::CarrierBase>(new com_layer::TcpServer);
  }

  return std::unique_ptr<com_layer::CarrierBase>(new com_layer::TcpClient);
}

}  // namespace

PostalService::PostalService(Type type) : carrier_(CarrierFactory(type)) {
  received_byte_array_.clear();
}

void PostalService::AsyncInit(
    const com_layer::ConnectionInfo& connection_info) {
  if (!carrier_) {
    return;
  }

  carrier_->Init(connection_info);
}

bool PostalService::WaitForOpen() {
  if (!carrier_) {
    return false;
  }

  int max_counter = kInitTimeout / std::chrono::milliseconds(50);
  int counter = 0;

  while (!IsOpen()) {
    if (counter++ > max_counter) {
      std::cerr << "Timout occured" << std::endl;
      return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  return true;
}

void PostalService::SendMail(const google::protobuf::Message& message) const {
  google::protobuf::Any any;
  any.PackFrom(message);

  std::string byte_array = any.SerializeAsString();
  carrier_->SendData(byte_array.data(), static_cast<int>(byte_array.size()));
}

void PostalService::GetMail(IMailDistributor& mail_distributor) {
  received_byte_array_ = carrier_->ReadByteArray();
  if (received_byte_array_.empty()) {
    return;
  }

  google::protobuf::Any any;
  any.ParseFromString(received_byte_array_);

  mail_distributor.Distribute(any);
  received_byte_array_.clear();
}

bool PostalService::IsOpen() const {
  if (!carrier_) {
    return false;
  }
  return carrier_->IsConnected();
}

}  // namespace postal_service
