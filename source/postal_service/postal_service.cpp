#include "postal_service/postal_service.h"

#include "external_libraries/protobuf/src/google/protobuf/any.pb.h"
#include "postal_service/com_layer/tcp_client.h"
#include "postal_service/com_layer/tcp_server.h"

namespace postal_service {

namespace {

std::unique_ptr<com_layer::ICarrier> CarrierFactory(Type type) {
  if (type == Type::server) {
    return std::unique_ptr<com_layer::ICarrier>(new com_layer::TcpServer);
  }

  return std::unique_ptr<com_layer::ICarrier>(new com_layer::TcpClient);
}

}  // namespace

PostalService::PostalService(Type type) : carrier_(CarrierFactory(type)) {}

void PostalService::Init() { carrier_->Init(); }

void PostalService::SendPostCard(IPostCard& post_card) const {
  google::protobuf::Any any = post_card.CreateProtobuf();
  std::string byte_array = any.SerializeAsString();
  carrier_->SendData(byte_array.data(), byte_array.size());
}

void PostalService::GetMail(IMailDistributor& mail_distributor) {
  carrier_->SwapReceivedByteArray(received_byte_array_);
  mail_distributor.Distribute(received_byte_array_);
  received_byte_array_.clear();
}

}  // namespace postal_service
