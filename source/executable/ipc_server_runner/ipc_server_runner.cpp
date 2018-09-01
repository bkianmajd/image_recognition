#include <QCoreApplication>

#include <iostream>
#include <thread>
#include "executable/ipc_server_runner/static_config.h"
#include "helpers/directory_finder.h"
#include "helpers/memory_helper.hpp"
#include "image_ipc/ipc_server/image_command_distributor.h"
#include "image_ipc/ipc_server/ipc_server_controller.h"
#include "postal_service/com_layer/tcp_server.h"

std::string GetFileManagerDirectory() {
  helpers::DirectoryFinder directory(
      ipc_server_runner::kFileManagerDataDirectory,
      helpers::DirectoryFinder::ReferenceFrame::RelativeToExec);
  return directory.GetAbsPath();
}

void RunControllerThread(QCoreApplication* a,
                         ipc::ipc_server::IpcServerController* ipc_controller) {
  // Controller run
  ipc_controller->Run();

  std::cout << "IPC Controller stopped running" << std::endl;
  a->quit();
}

int Main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  // Construction - PostalService
  std::unique_ptr<postal_service::PostalService> postal_service =
      std::make_unique<postal_service::PostalService>(
          postal_service::Type::server);

  // Construction - ImageCommandDistributor
  std::unique_ptr<ipc::ipc_server::FileManager> file_manager =
      std::make_unique<ipc::ipc_server::FileManager>(GetFileManagerDirectory());
  std::unique_ptr<ipc::ipc_server::ResponseHandler> response_handler =
      std::make_unique<ipc::ipc_server::ResponseHandler>();
  std::unique_ptr<ipc::ipc_server::ImageCommandDistributor>
      image_command_distributor =
          std::make_unique<ipc::ipc_server::ImageCommandDistributor>(
              file_manager.get(), response_handler.get());

  // Construction - IpcServerController
  std::unique_ptr<ipc::ipc_server::IpcServerController> ipc_server_controller =
      std::make_unique<ipc::ipc_server::IpcServerController>(
          postal_service.get(), image_command_distributor.get(),
          response_handler.get());

  // Initialization
  ipc_server_controller->Initialize();

  // Start thread and transfer ownership
  std::thread t1(RunControllerThread, &a, ipc_server_controller.get());

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
