#include "postal_service/postal_service.h"

#include <iostream>
#include <fstream>

#include "google_test/testing_def.h"
#include "external_libraries/googletest/include/gtest/gtest.h"

namespace postal_service {

namespace {
}  // namespace



class PostalServiceTest : public testing::Test {
public:
  PostalServiceTest() {}

protected:
    PostalService postal_service_;

};

TEST_F(PostalServiceTest, ConstructDestruct) {}


}  // namespace postal_service
