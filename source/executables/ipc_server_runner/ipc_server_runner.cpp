#include <QApplication>

#include <iostream>
#include <thread>

#include "components/image_service/server/ipc_server.h"
#include "components/poker/app_finder/app_finder.h"
#include "components/poker/workflow_session_thread.h"
#include "executables/ipc_server_runner/static_config.h"
#include "helpers/memory_helper.hpp"

void RunServerThread(QCoreApplication* a, ipc::IpcServer* ipc_server,
                     poker::WorkflowSessionThread* workflow_session_thread) {
  poker::AppFinder app_finder;
  auto start_time = std::chrono::system_clock::now();
  while (!ipc_server->IsInit()) {
    if (std::chrono::system_clock::now() - start_time > ipc_server::kTimeout) {
      std::cerr << "Could not initialize ipc server" << std::endl;
      a->quit();
      return;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  std::cout << "Initializing IPC server and starting session" << std::endl;
  workflow_session_thread->StartSession();
  bool run_mode = true;
  while (run_mode) {
    std::vector<char> image_bytes;

    // Check mail for screenshot
    if (!ipc_server->CheckForImage(&image_bytes)) {
      std::cerr << "Failed in com protocol" << std::endl;
      break;
    }

    // Check the image for the poker application
    std::vector<char> narrowed_image = app_finder.Narrow(image_bytes);

    // Send the image to the poker workflow
    if (narrowed_image.size() != 0) {
      // std::cout << "poker image recognized" << std::endl;
      // This runs the backend workflow
      workflow_session_thread->ProcessImage(narrowed_image);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  std::cout << "Stopping running thread" << std::endl;
  workflow_session_thread->EndSessionAndJoin();
  a->quit();
}

int Main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  // Construction - IpcServer
  std::unique_ptr<ipc::IpcServer> ipc_server =
      std::make_unique<ipc::IpcServer>();

  // Construction - poker component
  // Widgets must be created in main thread
  // template_recognition::ScreenshotCreator screenshot_creator;
  std::unique_ptr<poker::WorkflowSessionThread> poker_session_thread =
      std::make_unique<poker::WorkflowSessionThread>();

  // Initialization - has to be done on main thread
  com_layer::ConnectionInfo connection_info;
  connection_info.port = ipc_server::kPort;
  connection_info.connection_address = ipc_server::kConnectionAddress;
  ipc_server->AsyncInit(connection_info);

  // Start thread and transfer ownership
  std::thread t1(RunServerThread, &a, ipc_server.get(),
                 poker_session_thread.get());

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
