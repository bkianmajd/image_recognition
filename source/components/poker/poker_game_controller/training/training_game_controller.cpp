#include "components/poker/poker_game_controller/training/training_game_controller.h"

#include <cstdio>
#include <string>

#include "helpers/file_manager/file_manager.h"
#include "libraries/image_def/image_def.h"

#define ClearScreen() printf("\033[H\033[J")

namespace poker {
namespace {

constexpr char kDefaultDirectory[] =
    "components/poker/poker_game_controller/training/ignore_images";
constexpr char kCardRecordDirectory[] =
    "components/poker/poker_game_controller/training/ignore_cards";

enum Mode {
  MODE_UNKNOWN = 0,
  MODE_SCREENSHOT,
  MODE_READ_CARDS,
  MODE_RECORD_TABLE,
  MODE_RECORD_PLAYERS,
};

constexpr int kTableSize = 6;
constexpr Mode kMode = MODE_RECORD_PLAYERS;
const std::chrono::milliseconds kPrintPeriod = std::chrono::milliseconds(500);

}  // namespace

TrainingGameController::TrainingGameController()
    : directory_finder_(
          kDefaultDirectory,
          helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace),
      image_counter_(0),
      landmark_finder_(kTableSize),
      table_locator_(kTableSize),
      trainer_(
          helpers::CreateDirectoryFinderFromWorkspace(kCardRecordDirectory)) {
  if (kMode == MODE_RECORD_PLAYERS) {
    directory_finder_ =
        helpers::CreateDirectoryFinderFromWorkspace(kCardRecordDirectory);
  }

  for (int location = PLAYERLOC_PLAYER_ZERO; location < PLAYERLOC_PLAYER_SIX;
       ++location) {
    player_locator_.push_back(
        PlayerLocator(kTableSize, static_cast<PlayerLocation>(location)));
  }
}

void TrainingGameController::UpdateBigImage(
    const std::vector<char>& big_image_raw_data) {
  switch (kMode) {
    case MODE_SCREENSHOT:
      TakeScreenshots(big_image_raw_data);
      break;
    case MODE_READ_CARDS:
      ReadCards(big_image_raw_data);
      break;
    case MODE_RECORD_PLAYERS:
      RecordPlayers(big_image_raw_data);
      break;
    default:
      break;
  }
}

void TrainingGameController::RecordTable(
    const std::vector<char>& big_image_raw_data) {
  screenshot_creator_.Capture(big_image_raw_data);

  // Record Table dealer cards
  for (int i = DealerLocation::DEALER_ONE; i <= DealerLocation::DEALER_FIVE;
       ++i) {
    template_recognition::ScreenArea area =
        table_locator_.GetDealerArea(static_cast<DealerLocation>(i));
    image::Image card_image = screenshot_creator_.GetLastCapture(area);
    if (!AddCardToTrainer(card_image)) {
      // Card not recognized, record big image as well
      TakeScreenshots(big_image_raw_data);
    }
  }
}

void TrainingGameController::RecordPlayers(
    const std::vector<char>& big_image_raw_data) {
  screenshot_creator_.Capture(big_image_raw_data);

  // Record player cards
  for (PlayerLocator& player_locator : player_locator_) {
    // Adding left card
    template_recognition::ScreenArea left_area =
        player_locator.GetLeftCardArea();
    image::Image left_card_image =
        screenshot_creator_.GetLastCapture(left_area);
    if (!AddCardToTrainer(left_card_image)) {
      // Card not recognized, record big image as well
      TakeScreenshots(big_image_raw_data);
    }

    // Adding right card
    template_recognition::ScreenArea right_area =
        player_locator.GetRightCardArea();
    image::Image right_card_image =
        screenshot_creator_.GetLastCapture(right_area);
    if (!AddCardToTrainer(right_card_image)) {
      // Card not recognized, record big image as well
      TakeScreenshots(big_image_raw_data);
    }
  }
}

bool TrainingGameController::AddCardToTrainer(const image::Image& card_image) {
  // note: this is a copy and paste of the card reader private namespace
  constexpr int kDefaultWidth = 16;
  constexpr int kDefaultHeight = 17;
  const template_recognition::ScreenArea kValueArea(1, 3, kDefaultWidth,
                                                    kDefaultHeight);
  // Get the value of the card
  template_recognition::ScreenshotCreator sc;
  sc.Capture(card_image);
  image::Image value = sc.GetLastCapture(kValueArea);

  // Run the value through the pipeline
  // Make sure to only do noise reduction for recording cards
  pipeline_.ResetPipeline();
  pipeline_.AddToPipeline(image::PipelineType::NOISE_REDUCTION);
  pipeline_.AddToPipeline(image::PipelineType::TOP_LEFT_ALIGNMENT);
  auto image_vector = pipeline_.Run(value);
  assert(image_vector.size() == 1);
  image::Image& reduced_image = image_vector[0];

  // move the pipelined image to the trainer
  return trainer_.AddImage(reduced_image);
}

void TrainingGameController::ReadCards(
    const std::vector<char>& big_image_raw_data) {
  landmark_finder_.UpdateBigImage(big_image_raw_data);

  last_print_time_ = std::chrono::system_clock::now();
  if (std::chrono::system_clock::now() - last_print_time_ > kPrintPeriod) {
    last_print_time_ = std::chrono::system_clock::now();

    ClearScreen();
    std::cout << "Player zero " << std::endl;
    std::cout
        << "L: "
        << landmark_finder_.FindLeftCard(PlayerLocation::PLAYERLOC_PLAYER_ZERO)
        << " R: "
        << landmark_finder_.FindRightCard(PlayerLocation::PLAYERLOC_PLAYER_ZERO)
        << std::endl;
    std::cout << "Dealer cards " << std::endl;
    std::cout << "1: "
              << landmark_finder_.FindDealerCard(DealerLocation::DEALER_ONE)
              << " 2: "
              << landmark_finder_.FindDealerCard(DealerLocation::DEALER_TWO)
              << " 3: "
              << landmark_finder_.FindDealerCard(DealerLocation::DEALER_THREE)
              << " 4: "
              << landmark_finder_.FindDealerCard(DealerLocation::DEALER_FOUR)
              << " 5: "
              << landmark_finder_.FindDealerCard(DealerLocation::DEALER_FIVE)
              << std::endl;
  }
}

bool TrainingGameController::ProcessNextWorkflow(
    const GameStatus& game_status) {
  (void)game_status;
  return false;
}

void TrainingGameController::TakeScreenshots(
    const std::vector<char>& big_image_raw_data) {
  std::stringstream ss;
  ss << image_counter_++ << ".jpg";
  // Store the file
  helpers::FileManager::StoreFile(
      big_image_raw_data.data(), big_image_raw_data.size(),
      directory_finder_.GetAbsPathOfTargetFile(ss.str()));
}

}  // namespace poker
