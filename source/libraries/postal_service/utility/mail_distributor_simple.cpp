#include "libraries/postal_service/utility/mail_distributor_simple.h"

#include <iostream>
#include "external_libraries/protobuf-3.5.x/src/google/protobuf/any.pb.h"
#include "schema/compiled_files/test_proto.pb.h"

namespace postal_service {

void MailDistributorSimple::Distribute(const google::protobuf::Any& any) {
  if (any.Is<TestProto>()) {
    TestProto test;
    any.UnpackTo(&test);
    if (test.test_bool()) {
      std::cout << "true" << std::endl;
    }
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
