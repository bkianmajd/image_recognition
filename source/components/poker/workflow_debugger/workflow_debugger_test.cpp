#include "components/poker/workflow_debugger/workflow_debugger.h"

#include <iostream>

#include "gtest/gtest.h"
#include "helpers/file_manager/file_manager.h"

namespace poker {
namespace {

const std::string kTestDirectory =
    "components/poker/workflow_debugger/test_directory";
const std::string kErrorImage = "sample_error_image.jpg";
const std::string kTestErrorString = "this is a test";

}  // namespace

class WorkflowDebuggerTest : public testing::Test {
 public:
  WorkflowDebuggerTest()
      : testing_directory_(
            helpers::CreateDirectoryFinderFromWorkspace(kTestDirectory)) {}

 protected:
  helpers::DirectoryFinder testing_directory_;
  WorkflowDebugger workflow_debugger_;
};
TEST_F(WorkflowDebuggerTest, ConstructDestruct) {}

TEST_F(WorkflowDebuggerTest, ErrorTest) {
  // Change error directory
  workflow_debugger_.error_log_directory_ = testing_directory_;
  workflow_debugger_.ResetLogFile();

  // Load a sample error image
  std::vector<char> image = helpers::FileManager::ReadFile(
      testing_directory_.GetAbsPathOfTargetFile(kErrorImage));
  ASSERT_GT(image.size(), 0);

  workflow_debugger_.StoreError(image, kTestErrorString);
  workflow_debugger_.StoreError(image, kTestErrorString);

  // Expect to see 2 new images in the directory
}

}  // namespace poker
