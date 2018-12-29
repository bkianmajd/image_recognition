#include <QCoreApplication>
#include <QString>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class DirectoryFinder {
 public:
  DirectoryFinder(const std::string& workspace, char slash_type,
                  const char* directory)
      : workspace_(workspace), slash_type_(slash_type), directory_(directory) {
    PopulateDirectory(directory);
    PopulateStringPaths();
  }

  int GetWorkspaceIndex() const { return workspace_index_; }

  std::string GetBackSlashWorkspace() const {
    std::string ret;
    int backward_slash_count = GetSize() - GetWorkspaceIndex();
    for (int i = 0; i < backward_slash_count; ++i) {
      ret += "../";
    }
    ret += GetWorkspaceName();
    ret += "/";
    return ret;
  }

  std::string GetAfterWorkspace() const {
    std::string ret;
    // The size
    for (int i = GetWorkspaceIndex() + 1; i < GetSize(); ++i) {
      ret += GetString(i);
      ret += '/';
    }
    return ret;
  }

  std::string GetLastFolderName() const { return *(string_paths_.end() - 1); }

  int GetSize() const { return string_paths_.size(); }

  std::string GetString(unsigned int index) const {
    if (index < string_paths_.size()) {
      return string_paths_[index];
    }
    return "";
  }

  std::string GetWorkspaceName() const { return workspace_; }

 private:
  void PopulateDirectory(const char* str) {
    /*
    int index = 0;
    while(str[index] != '0' && str[index] != '!') {
      directory_ << str[index++];
    }
    */
    (void)str;
    QString test = QCoreApplication::applicationDirPath();

    for (int i = 0; i < test.size(); ++i) {
      directory_ << test.at(i).toLatin1();
    }
    std::cout << "Found directory: " << directory_.str() << std::endl;
  }

  bool GetNextString(std::string* str) {
    str->clear();
    char next;
    next = directory_.get();
    while (next != slash_type_) {
      if (next == '0' || !directory_.good()) {
        return false;
      }
      *str += next;
      next = directory_.get();
    }

    return true;
  }

  void PopulateStringPaths() {
    std::string next_str;
    int index = 0;

    while (GetNextString(&next_str)) {
      if (next_str.compare(workspace_) == 0) {
        workspace_index_ = index;
      }

      index++;
      string_paths_.push_back(next_str);
    }
    string_paths_.push_back(next_str);
  }

  std::string workspace_;
  char slash_type_;
  std::stringstream directory_;
  std::vector<std::string> string_paths_;
  int workspace_index_ = -1;
};

namespace output {

std::string CreateTestPro(const DirectoryFinder& directory_finder,
                          const std::string& file_input) {
  std::stringstream stream;

  stream << "QT += core" << std::endl;
  stream << "QT -= gui" << std::endl;
  stream << std::endl;
  stream << "CONFIG += c++14" << std::endl;
  stream << std::endl;

  stream << "WORKSPACE = $$_PRO_FILE_PWD_/"
         << directory_finder.GetBackSlashWorkspace() << std::endl;
  stream << "INCLUDEPATH += $${WORKSPACE}" << std::endl;
  stream << "INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include"
         << std::endl;
  stream << std::endl;

  stream << "LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a"
         << std::endl;
  stream << std::endl;

  stream << "SOURCES += $${WORKSPACE}/google_test/main.cpp" << std::endl;
  stream << "SOURCES += $${WORKSPACE}/" << directory_finder.GetAfterWorkspace()
         << file_input << "_test.cpp" << std::endl;
  stream << std::endl;

  stream << "include($${WORKSPACE}/" << directory_finder.GetAfterWorkspace()
         << file_input << ".pri)" << std::endl;
  return stream.str();
}

std::string CreatePri(const DirectoryFinder& directory_finder,
                      const std::string& file_input) {
  std::stringstream stream;
  stream << "!contains(included_modules, $$PWD ) {" << std::endl;
  stream << "included_modules += $$PWD" << std::endl;
  stream << "HEADERS += "
         << "$${WORKSPACE}/" << directory_finder.GetAfterWorkspace()
         << file_input << ".h" << std::endl;
  stream << std::endl;
  stream << "SOURCES += "
         << "$${WORKSPACE}/" << directory_finder.GetAfterWorkspace()
         << file_input << ".cpp" << std::endl;
  stream << "}" << std::endl;
  return stream.str();
}

std::string GetCap(const std::string& uncap_str) {
  std::stringstream cap_str;
  for (unsigned int i = 0; i < uncap_str.size(); ++i) {
    if (uncap_str[i] == '_') {
      cap_str << uncap_str[i];
    } else {
      cap_str << static_cast<char>(uncap_str[i] - 32);
    }
  }
  return cap_str.str();
}

std::string GetClassName(const std::string& file_input) {
  std::stringstream class_name;
  bool should_cap = true;

  for (unsigned int i = 0; i < file_input.size(); ++i) {
    if (file_input[i] == '_') {
      should_cap = true;
      continue;
    }

    if (should_cap) {
      should_cap = false;
      class_name << static_cast<char>(file_input[i] - 32);
    } else {
      class_name << file_input[i];
    }
  }
  return class_name.str();
}

std::string CreateHeader(const DirectoryFinder& directory_finder,
                         const std::string& file_input) {
  (void)directory_finder;
  std::stringstream stream;
  stream << "#ifndef " << GetCap(file_input) << "_H_" << std::endl;
  stream << "#define " << GetCap(file_input) << "_H_" << std::endl;
  stream << std::endl;

  stream << "namespace " << directory_finder.GetLastFolderName() << " {"
         << std::endl;
  stream << std::endl;
  stream << "class " << GetClassName(file_input) << " {" << std::endl;
  stream << "public:" << std::endl;
  stream << "  " << GetClassName(file_input) << "();" << std::endl;
  stream << std::endl;
  stream << "private:" << std::endl;
  stream << std::endl;
  stream << "};" << std::endl;
  stream << std::endl;
  stream << "}  // namespace " << directory_finder.GetLastFolderName()
         << std::endl;
  stream << std::endl;
  stream << "#endif  // " << GetCap(file_input) << "_H_" << std::endl;

  return stream.str();
}

std::string CreateSource(const DirectoryFinder& directory_finder,
                         const std::string& file_input) {
  std::stringstream stream;
  stream << "#include \"" << directory_finder.GetAfterWorkspace() << file_input
         << ".h\"" << std::endl;
  stream << std::endl;
  stream << "namespace " << directory_finder.GetLastFolderName() << " {"
         << std::endl;
  stream << std::endl;
  stream << GetClassName(file_input) << "::" << GetClassName(file_input)
         << "() {}" << std::endl;
  stream << std::endl;
  stream << "}  // namespace " << directory_finder.GetLastFolderName()
         << std::endl;

  return stream.str();
}

std::string CreateTestCC(const DirectoryFinder& directory_finder,
                         const std::string& file_input) {
  std::stringstream stream;

  stream << "#include \"" << directory_finder.GetAfterWorkspace() << file_input
         << ".h\"";
  stream << std::endl;
  stream << std::endl;
  stream << "#include <iostream>" << std::endl;
  stream << std::endl;
  stream << "#include \"gtest/gtest.h\"" << std::endl;
  stream << std::endl;
  stream << "namespace " << directory_finder.GetLastFolderName() << " {"
         << std::endl;
  stream << std::endl;
  stream << "class " << GetClassName(file_input) << "Test : "
         << "public testing::Test {" << std::endl;
  stream << "public:" << std::endl;
  stream << GetClassName(file_input) << "Test() {}" << std::endl;
  stream << std::endl;
  stream << "protected:" << std::endl;
  stream << std::endl;
  stream << "};" << std::endl;
  stream << "TEST_F(" << GetClassName(file_input)
         << "Test, ConstructDestruct) {}" << std::endl;
  stream << std::endl;
  stream << "}  // namespace " << directory_finder.GetLastFolderName()
         << std::endl;
  stream << std::endl;

  return stream.str();
}

}  // namespace output

namespace {

const char kSlash = '/';
const std::string kWorkspace = "source";

void WriteToFile(const std::string& file_name, const std::string& payload) {
  std::ofstream my_file;
  my_file.open(file_name);

  my_file << payload;
  my_file.close();
}

}  // namespace

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);
  std::stringstream file_input;

  std::cout << "number of inputs " << argc << "\n";

  if (argc < 2) {
    std::cout << "no input\n";
    file_input << "test_class";
    return -1;
  } else {
    // Find file input
    char* file_str = argv[1];
    int index = 0;
    while (file_str[index] != '0' && file_str[index] != '!') {
      file_input << file_str[index++];
    }
    if (file_str[index] == '0') {
      std::cout << "need !" << std::endl;
      return -1;
    }
    std::cout << "Found file input: " << file_input.str() << std::endl;
  }

  // Find source directory
  char* str = argv[0];
  DirectoryFinder directory_finder(kWorkspace, kSlash, str);

  if (directory_finder.GetWorkspaceIndex() < 0) {
    std::cout << "Not found!\n";
    return -1;
  }

  std::cout << "writing files..." << std::endl;
  std::string file_name = file_input.str();

  // std::cout << output::CreateHeader(directory_finder, "test_class");
  WriteToFile(file_name + ".h",
              output::CreateHeader(directory_finder, file_name));

  // std::cout << output::CreateTestPro(directory_finder, "com_server") <<
  // std::endl;
  WriteToFile(file_name + ".pro",
              output::CreateTestPro(directory_finder, file_name));

  // std::cout << output::CreateSource(directory_finder, "test_class");
  WriteToFile(file_name + ".cpp",
              output::CreateSource(directory_finder, file_name));

  // std::cout << output::CreateTestCC(directory_finder, "test_class");
  WriteToFile(file_name + "_test.cpp",
              output::CreateTestCC(directory_finder, file_name));

  std::cout << output::CreatePri(directory_finder, "test_class");
  WriteToFile(file_name + ".pri",
              output::CreatePri(directory_finder, file_name));

  return 0;
}
