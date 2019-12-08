#include "components/menu_runner/menu_runner.h"

namespace poker {
namespace {

constexpr char kSingleImagePath[] = "components/menu_runner/images";
constexpr char kRecordingPath[] = "components/menu_runner/recording_images";

Card ConvertInputToCard(int value_input, int suit_input) {
  Card card;
  card.value = static_cast<CardValue>(value_input);
  card.suit = static_cast<Suit>(suit_input);
  return card;
}

}  // namespace

MenuRunner::MenuRunner(SessionThread<WorkflowSession>* session)
    : session_(session),
      single_image_path_(
          helpers::CreateDirectoryFinderFromWorkspace(kSingleImagePath)),
      recording_path_(
          helpers::CreateDirectoryFinderFromWorkspace(kRecordingPath)) {}

bool MenuRunner::KeepRunning() const { return keep_running_; }

void MenuRunner::ProcessUserInput() {
  ShowMenu();

  // Handle user input
  int user_input = 0;
  std::cin >> user_input;
  switch (user_input) {
    case 1:
      RecordSingleImage();
      break;
    case 2: {
      PlayerHand player_hand = QueryInjectedHand();
      session_->PostTask(&WorkflowSession::InjectNewHand, player_hand);
      break;
    }
    case 3:
      session_->PostTask(&WorkflowSession::ClearInjection);
      break;
    case 4:
      session_->PostTask(&WorkflowSession::ForceDecision);
      break;
    case 5:
      Record();
      break;
    case 9:
      keep_running_ = false;
      break;
    default:
      break;
  }
}

void MenuRunner::RecordSingleImage() {
  // Create the file name
  std::stringstream ss;
  ss << last_debug_number_ << ".jpg";
  last_debug_number_++;
  std::string file_abs_path =
      single_image_path_.GetAbsPathOfTargetFile(ss.str());

  session_->PostTask(&WorkflowSession::SaveImageToDebug, file_abs_path);
}

void MenuRunner::Record() {
  int recording_debuging_number = 0;

  // Start a 60 second timer
  base::Time start = base::Time::Now();
  base::TimeDelta delta = base::TimeDelta::FromSeconds(60);

  std::cout << "Recording for 60 seconds..." << std::endl;

  // Create the file name
  while (base::Time::Now() - start < delta) {
    std::stringstream ss;
    ss << recording_debuging_number << ".jpg";
    recording_debuging_number++;
    std::string file_abs_path =
        recording_path_.GetAbsPathOfTargetFile(ss.str());
    session_->PostTask(&WorkflowSession::SaveImageToDebug, file_abs_path);
    usleep(1000);
  }
  std::cout << "Finished recording" << std::endl;
}

void MenuRunner::ShowMenu() {
  // Create the run menu
  std::stringstream ss;
  ss << "---------------" << std::endl;
  ss << "[1] Save Current Image " << std::endl;
  ss << "[2] Inject Test Card" << std::endl;
  ss << "[3] Stop Injecting Card " << std::endl;
  ss << "[4] Force Decision " << std::endl;
  ss << "[5] Record for 60 seconds" << std::endl;
  ss << "[9] Exit Application" << std::endl;
  ss << "---------------" << std::endl;

  std::cout << ss.str();
}

PlayerHand MenuRunner::QueryInjectedHand() const {
  PlayerHand player_hand;
  int value_input;
  int suit_input;
  // Create the injected hand menu
  std::cout << "Inject card to be player's hand!" << std::endl;
  std::cout << "Input first card value (1 - 13) Ace is one, King is 13"
            << std::endl;
  std::cin >> value_input;
  std::cout
      << "Input first card suit (1 = Spade, 2 = Club, 3 = Diamond, 4 = Heart)"
      << std::endl;
  std::cin >> suit_input;
  player_hand.FirstCard() = ConvertInputToCard(value_input, suit_input);

  std::cout << "Input second card value (1 - 13) Ace is one, King is 13"
            << std::endl;
  std::cin >> value_input;
  std::cout
      << "Input second card suit (1 = Spade, 2 = Club, 3 = Diamond, 4 = Heart)"
      << std::endl;
  std::cin >> suit_input;
  player_hand.SecondCard() = ConvertInputToCard(value_input, suit_input);
  return player_hand;
}

}  // namespace poker
