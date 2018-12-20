#include <QCoreApplication>

#include <iostream>
#include <thread>

#include "components/image_service/client/ipc_client.h"
#include "executables/ipc_client_runner/static_config.h"
#include "helpers/memory_helper.hpp"
#include "libraries/postal_service/com_layer/com_defs.h"
#include "libraries/postal_service/postal_service.h"

/*
void RunControllerThread(QCoreApplication* a,
                         ipc::ipc_server::IpcServerController* ipc_controller) {
  // Controller run
  ipc_controller->Run();

  std::cout << "IPC Controller stopped running" << std::endl;
  a->quit();
}
*/

int Main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  // Construction - PostalService
  std::unique_ptr<postal_service::PostalService> postal_service =
      std::make_unique<postal_service::PostalService>(
          postal_service::Type::client);

  // Get connection info
  com_layer::ConnectionInfo connection_info;
  connection_info.port = ipc_client::kPort;
  connection_info.connection_address = ipc_client::kConnectionAddress;

  postal_service->AsyncInit(connection_info);
  /*
        // Construction - IpcClient
        ipc::IpcClient ipc_client;

    std::unique_ptr<ipc::ipc_client::IpcClientController> ipc_server_controller
    =
        std::make_unique<ipc::ipc_server::IpcServerController>(
            postal_service.get(), image_command_creator.get(),
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
  */
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
