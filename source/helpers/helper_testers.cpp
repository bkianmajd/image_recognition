#include "helpers/directory_finder.h"

#include <iostream>
#include "gtest/gtest.h"

namespace helpers {

TEST(DirectoryFinderTest, workspace_directory) {
  DirectoryFinder directory_finder("");
  std::cout << directory_finder.GetAbsPathRelativeToExecutable() << std::endl;
  std::cout << directory_finder.GetAbsPathRelativeToWorkspace() << std::endl;

  DirectoryFinder directory_finder2("test/image.jpg");
  std::cout << directory_finder2.GetAbsPathRelativeToExecutable() << std::endl;
  std::cout << directory_finder2.GetAbsPathRelativeToWorkspace() << std::endl;
}

}  // namespace helpers
