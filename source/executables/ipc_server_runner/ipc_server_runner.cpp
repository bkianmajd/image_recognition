#include <QCoreApplication>

#include <iostream>
#include <thread>

#include "components/image_service/server/ipc_server.h"
#include "components/poker/poker_workflow.h"
#include "executables/ipc_server_runner/static_config.h"
#include "helpers/memory_helper.hpp"

void RunControllerThread(QCoreApplication* a, ipc::IpcServer* ipc_server,
                         poker::PokerWorkflow* poker_workflow) {
  auto start_time = std::chrono::system_clock::now();
  while (!ipc_server->IsInit()) {
    if (std::chrono::system_clock::now() - start_time > ipc_server::kTimeout) {
      std::cerr << "Could not initialize ipc server" << std::endl;
      a->quit();
      return;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  bool run_mode = true;
  while (run_mode) {
    std::vector<char> image_bytes;

    // Check mail for screenshot
    if (!ipc_server->CheckForImage(&image_bytes)) {
      std::cerr << "Failed in com protocol";
      break;
    }

    // Send the image to the poker workflow
    if (image_bytes.size() != 0) {
      std::cout << "new image obtained" << std::endl;
      poker_workflow->ConsumeImage(image_bytes);
      // This runs the backend workflow
      // TODO(): Consider running this in a separate thread
      poker_workflow->ProcessImage();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  std::cout << "Stopping running thread" << std::endl;
  a->quit();
}

int Main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  // Construction - IpcServer
  std::unique_ptr<ipc::IpcServer> ipc_server =
      std::make_unique<ipc::IpcServer>();

  // Construction - poker component
  std::unique_ptr<poker::PokerWorkflow> poker_workflow =
      std::make_unique<poker::PokerWorkflow>();

  // Initialization - has to be done on main thread
  com_layer::ConnectionInfo connection_info;
  connection_info.port = ipc_server::kPort;
  connection_info.connection_address = ipc_server::kConnectionAddress;
  ipc_server->AsyncInit(connection_info);

  // Start thread and transfer ownership
  std::thread t1(RunControllerThread, &a, ipc_server.get(),
                 poker_workflow.get());

  // Run the main thread in the background
  a.exec();

  // Close the threads
  std::cout << "Returning" << std::endl;
  t1.join();

  return 0;
}

int main(int argc, char* argv[]) {
  try {
    return Main(argc, argv);
  } catch (...) {
    std::cerr << "Catch all error" << std::endl;
  }

  return -1;
}
