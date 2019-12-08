#include "components/poker/workflow_debugger/workflow_debugger.h"

#include <fstream>
#include <iostream>

#include "helpers/file_manager.h"

namespace poker {
namespace {

const std::string kSessionDirectory =
    "components/poker/workflow_debugger/error_logs";
const std::string kLogFile = "log_file.txt";

}  // namespace

WorkflowDebugger::WorkflowDebugger(DebugType debug_type)
    : status_change_counter_(0),
      error_identifier_(0),
      error_log_directory_(
          helpers::CreateDirectoryFinderFromWorkspace(kSessionDirectory)),
      debug_type_(debug_type) {
  // Reset the text file, do not append
  ResetLogFile();
}

void WorkflowDebugger::ResetLogFile() {
  std::ofstream txt_file(error_log_directory_.GetAbsPathOfTargetFile(kLogFile),
                         std::ios::trunc);
  if (!txt_file.is_open()) {
    std::cerr << "Error text file not found"
              << error_log_directory_.GetAbsPathOfTargetFile(kLogFile)
              << std::endl;
  }
}

void WorkflowDebugger::StoreError(const image::Image& image_error,
                                  const std::string& error_str) {
  std::cout << "Error detected: storing error: " << error_identifier_
            << std::endl;
  std::cerr << error_str << std::endl;

  // Storing text by appending to the text file
  std::ofstream txt_file(error_log_directory_.GetAbsPathOfTargetFile(kLogFile),
                         std::ios::app);
  if (!txt_file.is_open()) {
    std::cerr << "failed to store error" << std::endl;
    return;
  }

  txt_file << "[" << error_identifier_ << "] " << error_str << std::endl;

  // Storing image
  std::stringstream error_image_file_name;
  error_image_file_name << "img_error_" << error_identifier_ << ".jpg";
  helpers::FileManager::StoreFile(
      image_error.data(), image_error.size(),
      error_log_directory_.GetAbsPathOfTargetFile(error_image_file_name.str()));

  // increment the error identifier
  error_identifier_++;
}

void WorkflowDebugger::PrintNewHand(const GameModel& game_model) {
  const PlayerHand& player_hand =
      game_model.player_hands[PLAYERLOC_PLAYER_ZERO];
  std::cout << "Player deal " << player_hand.FirstCard() << " "
            << player_hand.SecondCard() << std::endl
            << std::endl;
}

void WorkflowDebugger::PrintStatusChange(const GameModel& game_model) {
  if (debug_type_ != PRINT_GAME_MODEL) {
    return;
  }
  status_change_counter_++;
  std::cout << "Game model update " << status_change_counter_++ << std::endl;

  // Print out the dealer cards
  std::cout << "D: ";
  for (size_t i = DEALER_ONE; i < DEALER_MAX_SIZE; ++i) {
    std::cout << game_model.dealer_cards.at(i);
    std::cout << " ";
  }
  std::cout << std::endl << std::endl;

  // Print out player cards
  for (size_t i = PLAYERLOC_PLAYER_ZERO; i < PLAYERLOC_PLAYER_SIX; ++i) {
    std::cout << "P[" << i << "] " << game_model.player_hands[i];
  }
  std::cout << std::endl;
}

void WorkflowDebugger::PrintStatusChange(const WorkflowModel& model) {
  if (debug_type_ != PRINT_WORKFLOW_MODEL) {
    return;
  }

  std::cout << "Number of opponents/original opponents: "
            << model.number_of_active_opponents << "/"
            << model.number_of_original_opponents << std::endl;
  PrintDealerCards(model.dealer_cards);
  std::cout << "P: " << model.player_hand << std::endl;
}

void WorkflowDebugger::PrintDealerCards(
    const std::array<Card, DEALER_MAX_SIZE>& dealer_cards) const {
  // Print out the dealer cards
  std::cout << "D: ";
  for (size_t i = DEALER_ONE; i < DEALER_MAX_SIZE; ++i) {
    std::cout << dealer_cards.at(i);
    std::cout << " ";
  }
  std::cout << std::endl;
}

void WorkflowDebugger::PrintDecision() {}

}  // namespace poker
