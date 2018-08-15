#include "helpers/directory_finder.h"

#include <QCoreApplication>
#include <QDirIterator>
#include <QString>
#include <cassert>
#include <sstream>
#include <string>

namespace helpers {

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

}  // namespace

DirectoryFinder::DirectoryFinder(const char* directory_relative_to_executable) {
  FindAbsExecutablePath();
  abs_path_relative_executable_ += abs_executable_path_;
  abs_path_relative_executable_ += kSlash;
  abs_path_relative_executable_ += directory_relative_to_executable;

  FindWorkspaceDirectoryPath();
  abs_path_relative_workspace_ = workspace_directory_path_;
  abs_path_relative_workspace_ += kSlash;
  abs_path_relative_workspace_ += directory_relative_to_executable;
}

std::string DirectoryFinder::GetAbsPathRelativeToExecutable() const {
  return abs_path_relative_executable_;
}

std::string DirectoryFinder::GetAbsPathRelativeToWorkspace() const {
  return abs_path_relative_workspace_;
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
