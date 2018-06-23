#include "postal_service/mail_distributor_simple/mail_distributor_simple.h"

#include <iostream>
#include "external_libraries/protobuf/src/google/protobuf/any.pb.h"
#include "schema/compiled_files/test_proto.pb.h"

namespace postal_service {

void MailDistributorSimple::Distribute(std::string& string) {
  google::protobuf::Any any;
  any.ParseFromString(string);

  if (any.Is<TestProto>()) {
    TestProto test;
    any.UnpackTo(&test);
    std::cout << test.test_bool() << std::endl;
    std::cout << test.test_int() << std::endl;
    return;
  };

  std::cout << "false" << std::endl;

  // for (char a : string) {
  //  std::cout << (int)a << ",";
  //}
  // std::cout << std::endl;
}

}  // namespcae postal_service
