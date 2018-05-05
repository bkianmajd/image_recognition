#ifndef POSTAL_SERVICE_POST_CARDS_TEST_POST_CARD_H_
#define POSTAL_SERVICE_POST_CARDS_TEST_POST_CARD_H_

#include "external_libraries/protobuf/src/google/protobuf/any.pb.h"
#include "postal_service/ipost_card.h"
#include "schema/compiled_files/test_proto.pb.h"

namespace postal_service {

struct Test {
  bool value = true;
  int x = 1234;
};

class TestPostCard : public IPostCard {
 public:
  explicit TestPostCard(Test test) : test_(test) {}

  google::protobuf::Any CreateProtobuf() override {
    test_proto_.set_test_bool(test_.value);
    test_proto_.set_test_int(test_.x);
    google::protobuf::Any any;
    any.PackFrom(test_proto_);
    return any;
  }

 private:
  Test test_;
  TestProto test_proto_;
};

}  // namespace postal_service

#endif  // POSTAL_SERVICE_POST_CARDS_TEST_POST_CARD_H_
