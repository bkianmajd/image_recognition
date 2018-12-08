#include "helpers/directory_finder.h"

#include <iostream>
#include "google_test/testing_def.h"
#include "gtest/gtest.h"

namespace helpers {

TEST(DirectoryFinderTest, workspace_directory) {
  DirectoryFinder path_relative_to_executable(
      DirectoryFinder::ReferenceFrame::RelativeToExec);
  DirectoryFinder path_relative_to_workspace(
      DirectoryFinder::ReferenceFrame::RelativeToWorkspace);

  std::cout << "Relative to executable: "
            << path_relative_to_executable.GetAbsPath() << std::endl;
  std::cout << "Relative to workspace: "
            << path_relative_to_workspace.GetAbsPath() << std::endl;

  std::cout << "Relative to executable: "
            << path_relative_to_executable.GetAbsPathOfTargetFile("test.jpg")
            << std::endl;

  DirectoryFinder test_directory(
      "test", DirectoryFinder::ReferenceFrame::RelativeToWorkspace);
  std::cout << "Test directory: " << test_directory.GetAbsPath() << std::endl;
  std::cout << "Test file: "
            << test_directory.GetAbsPathOfTargetFile("test.jpg") << std::endl;

  DirectoryFinder workspace(
      tester::kTestingDirectoryFromWorkspace,
      helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace);
  std::cout << "Test directory workspace: " << workspace.GetAbsPath()
            << std::endl;
}

}  // namespace helpers
