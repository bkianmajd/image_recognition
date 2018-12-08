#include "image_ipc/ipc_server/image_command_dispatcher.h"

#include <iostream>
#include "google_test/testing_def.h"
#include "gtest/gtest.h"
#include "schema/compiled_files/test_proto.pb.h"
#include "template_recognition/template_recognition_mock.hpp"

namespace ipc {
namespace ipc_server {

class ImageCommandDispatcherTest : public testing::Test {
 public:
  ImageCommandDispatcherTest()
      : directory_finder_(
            testing_main::kTestingDirectoryFromWorkspace,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        image_command_dispatcher_(&directory_finder_, &file_manager_,
                                  &template_recognition_mock_) {}

 protected:
  helpers::DirectoryFinder directory_finder_;
  FileManager file_manager_;
  template_recognition::TemplateRecognitionMock template_recognition_mock_;
  ImageCommandDispatcher image_command_dispatcher_;
};
TEST_F(ImageCommandDispatcherTest, ConstructDestruct) {}

TEST_F(ImageCommandDispatcherTest, GetTemplateIdTest) {
  int template_id = image_command_dispatcher_.GetTemplateIdOrRegisterTemplate(
      testing_main::kImageOne);
  EXPECT_EQ(template_id, 0);

  template_id =
      image_command_dispatcher_.GetTemplateIdOrRegisterTemplate("some_other");
  EXPECT_EQ(template_id, 1);

  template_recognition_mock_.set_value_ = false;
  template_id =
      image_command_dispatcher_.GetTemplateIdOrRegisterTemplate("file_doesnt_exist");
  EXPECT_LT(template_id, 0);
}

}  // namespace ipc_server
}  // namespace ipc
