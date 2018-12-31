#include "helpers/directory_finder.h"

#include <QCoreApplication>
#include <QDirIterator>
#include <QString>
#include <cassert>
#include <sstream>
#include <string>

namespace helpers {

DirectoryFinder CreateDirectoryFinderFromWorkspace(const std::string& path) {
  return DirectoryFinder(path.c_str(),
                         DirectoryFinder::ReferenceFrame::RelativeToWorkspace);
}

namespace {

const std::string kWorkspace = "source";
const char kSlash = '/';

// Goes up one directory in the executable path by removing everything up to the
// next slash
QString GetStringUpOneDirectory(const QString& path) {
  return path.left(path.lastIndexOf(kSlash));
}

// Finds the file name after the last slash
QString GetNameAfterLastSlash(const QString& path) {
  QFileInfo fi(path);
  return fi.fileName();
}

std::string Convert(const QString& qstr) {
  std::stringstream ss;
  for (int i = 0; i < qstr.size(); ++i) {
    ss << qstr.at(i).toLatin1();
  }
  return ss.str();
}

// Always adds a slash to the target_directory unless the target_direcetory is
// empty
std::string VerifySlash(const char* target_directory) {
  std::string string_directory(target_directory);
  if (string_directory.size() == 0) {
    return string_directory;
  }

  if (string_directory.at(string_directory.size() - 1) != kSlash) {
    string_directory += kSlash;
  }

  return string_directory;
}

}  // namespace

DirectoryFinder::DirectoryFinder(const std::string& target_directory,
                                 ReferenceFrame reference_frame)
    : DirectoryFinder(target_directory.c_str(), reference_frame) {}

DirectoryFinder::DirectoryFinder(const char* target_directory,
                                 ReferenceFrame reference_frame) {
  FindAbsExecutablePath();
  FindWorkspaceDirectoryPath();

  // update abs directory path
  switch (reference_frame) {
    case ReferenceFrame::RelativeToExec:
      abs_target_directory_path_ = abs_executable_path_;
      break;
    case ReferenceFrame::RelativeToWorkspace:
      abs_target_directory_path_ = workspace_directory_path_;
      break;
  }

  abs_target_directory_path_ = VerifySlash(abs_target_directory_path_.c_str());
  abs_target_directory_path_.append(target_directory);
}

DirectoryFinder::DirectoryFinder(ReferenceFrame reference_frame)
    : DirectoryFinder("", reference_frame) {}

std::string DirectoryFinder::GetAbsPath() const {
  return abs_target_directory_path_;
}

std::string DirectoryFinder::GetAbsPathOfTargetFile(
    const std::string& file_name) const {
  std::string abs_target_path_of_file =
      VerifySlash(abs_target_directory_path_.c_str());
  abs_target_path_of_file.append(file_name.c_str());

  return abs_target_path_of_file;
}

void DirectoryFinder::FindWorkspaceDirectoryPath() {
  QString qstr(abs_executable_path_.c_str());
  while (!SearchForWorkspaceFolderInDirectory(qstr)) {
    qstr = GetStringUpOneDirectory(qstr);
    if (qstr.compare("") == 0) {
      // The execution should never reach this point meaning we couldnt find
      // the workspace directory from the executable location.
      assert(false);
    }
  }
}

bool DirectoryFinder::SearchForWorkspaceFolderInDirectory(const QString& path) {
  QDirIterator it(path, QDirIterator::Subdirectories);

  // SearchForWorkspaceFolderInDirectory
  QString sub_directory_path;
  while (it.hasNext()) {
    sub_directory_path = it.next();
    QString sub_directory_folder = GetNameAfterLastSlash(sub_directory_path);
    if (sub_directory_folder.compare(kWorkspace.c_str()) == 0) {
      workspace_directory_path_ = Convert(sub_directory_path);
      return true;
    }
  }
  return false;
}

void DirectoryFinder::FindAbsExecutablePath() {
  QString qstr = QCoreApplication::applicationDirPath();
  abs_executable_path_ = Convert(qstr);
}

}  // namespace helpers
