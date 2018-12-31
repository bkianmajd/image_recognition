#ifndef DIRECTORY_FINDER_H_
#define DIRECTORY_FINDER_H_

#include <QCoreApplication>
#include <sstream>
#include <string>

namespace helpers {

class DirectoryFinder;

DirectoryFinder CreateDirectoryFinderFromWorkspace(const std::string&);

/// This class returns the abs path of the specified target. The specified
/// directory is passed through the constructor.
class DirectoryFinder {
 public:
  enum class ReferenceFrame {
    RelativeToExec = 0,
    RelativeToWorkspace,
    // RelativeToPro,
  };

  /// The target directory is specified. This is a relative directory.
  DirectoryFinder(const std::string& target_directory,
                  ReferenceFrame reference_frame);
  DirectoryFinder(const char* target_directory, ReferenceFrame reference_frame);
  explicit DirectoryFinder(ReferenceFrame reference_frame);

  std::string GetAbsPath() const;

  std::string GetAbsPathOfTargetFile(const std::string& file_name) const;

 private:
  void FindWorkspaceDirectoryPath();

  bool SearchForWorkspaceFolderInDirectory(const QString& path);

  void FindAbsExecutablePath();

  // The current directory of the executable
  std::string abs_executable_path_;

  std::string workspace_directory_path_;

  std::string abs_target_directory_path_;
};

}  // namespace helpers

#endif  // DIRECTORY_FINDER_H_
