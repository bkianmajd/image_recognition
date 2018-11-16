#include "generic_bot/wow/sensor/wow_detectors/generic_detector.h"

#include <iostream>

#include "google_test/testing_def.h"
#include "gtest/gtest.h"
#include "helpers/directory_finder.h"
#include "template_recognition/simple/simple_recognition.h"

namespace bot {
namespace wow {
namespace {
const std::string kTemplateDirectory = "generic_bot/wow/wow_template_data";
const std::string kFireballName = "fireball.jpg";

DetectedObject CreateFireballPrototype() {
  DetectedObject detected_object;
  detected_object.image_type = ImageType::IMAGE_TYPE_PLAYER_SPELL;
  detected_object.player_spell = PlayerSpell::PLAYER_SPELL_FIREBALL;
  return detected_object;
}

}  // namespace

class WowDetectorTest : public testing::Test {
 public:
  WowDetectorTest()
      : template_directory_(
            kTemplateDirectory,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        test_directory_(
            testing_main::kTestingDirectoryFromWorkspace,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        session_directory_(
            testing_main::kSessionDirectoryFromWorkspace,
            helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
        template_recognition_manager_(session_directory_,
                                      &simple_recognition_),
        fireball_(kFireballName, CreateFireballPrototype(),
                  &template_recognition_manager_) {}

 protected:
  helpers::DirectoryFinder template_directory_;
  helpers::DirectoryFinder test_directory_;
  helpers::DirectoryFinder session_directory_;
  template_recognition::SimpleRecognition simple_recognition_;
  template_recognition::TemplateRecognitionManager
      template_recognition_manager_;
  GenericDetector fireball_;
};

TEST_F(WowDetectorTest, ConstructDestruct) {}

TEST_F(WowDetectorTest, RegisterImage) {
  EXPECT_TRUE(fireball_.RegisterTemplateImages(template_directory_));

  // Add big image
  std::string image_path_file =
      test_directory_.GetAbsPathOfTargetFile(testing_main::kBigImage);
  std::vector<char> bytes = helpers::FileManager::ReadFile(image_path_file);
  EXPECT_TRUE(
      template_recognition_manager_.StoreImage(testing_main::kBigImage, bytes));

  // Search for image
  template_recognition::Point point;
  EXPECT_TRUE(template_recognition_manager_.TemplateMatch(
      testing_main::kBigImage, kFireballName, &point));

  EXPECT_TRUE(point.isValid);
}

}  // namespace bot
}  // namespace wow
