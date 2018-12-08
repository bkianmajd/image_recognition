#ifndef TESTING_DEF_H_
#define TESTING_DEF_H_

#include "helpers/directory_finder.h"

namespace tester {

const std::string kWorkspaceFromTestingMain = "../../../source/";

const std::string kTestingDirectoryFromWorkspace = "google_test/test_data/";

const std::string kTemplateCheckers = "test.jpg";
const std::string kBigImageChecker = "left01.jpg";

const std::string kNoFile = "no_file.jpg";
const std::string kBigImage = "big_image_1.jpg";

const std::string kBigImagePokerTable = "poker_table.jpg";
const std::string kBigImagePokerTable2 = "poker_table2.jpg";
const std::string kBigImagePokerTable3 = "poker_table3.jpg";
const std::string kTemplate3Hearts = "3_hearts.jpg";
const std::string kTemplate7Clubs = "7_clubs.jpg";
const std::string kBigImageCardDef = "cards_big_image.jpg";

class Tester {
 public:
  Tester()
      : test_directory_(
            kTestingDirectoryFromWorkspace,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace) {}

  std::string GetAbsPath(const std::string& string) {
    return test_directory_.GetAbsPathOfTargetFile(string);
  }

 private:
  const helpers::DirectoryFinder test_directory_;
};

}  // tester

#endif  // TESTING_DEF_H_
