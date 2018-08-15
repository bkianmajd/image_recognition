#ifndef DIRECTORY_FINDER_H_
#define DIRECTORY_FINDER_H_

#include <QCoreApplication>
#include <sstream>
#include <string>

namespace helpers {

class DirectoryFinder {
 public:
  DirectoryFinder(const char* directory_relative_to_executable = "");

  std::string GetAbsPathRelativeToExecutable() const;

  std::string GetAbsPathRelativeToWorkspace() const;

 private:
  void FindWorkspaceDirectoryPath();

  bool SearchForWorkspaceFolderInDirectory(const QString& path);

  void FindAbsExecutablePath();

  // The current directory of the executable
  std::string abs_executable_path_;

  std::string workspace_directory_path_;

  std::string abs_path_relative_executable_;

  std::string abs_path_relative_workspace_;
};

}  // namespace helpers

#endif  // DIRECTORY_FINDER_H_
