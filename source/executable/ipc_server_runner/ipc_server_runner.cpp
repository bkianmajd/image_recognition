#include <QCoreApplication>

#include <iostream>
#include <thread>
#include "executable/ipc_server_runner/static_config.h"
#include "helpers/directory_finder.h"
#include "helpers/memory_helper.hpp"
#include "image_ipc/ipc_server/image_command_creator.h"
#include "image_ipc/ipc_server/ipc_server_controller.h"
#include "postal_service/com_layer/tcp_server.h"
#include "postal_service/utility/post_card_queue.h"
#include "template_recognition/simple/simple_recognition.h"

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

  // Define the session directory
  std::unique_ptr<helpers::DirectoryFinder> session_directory_ =
      std::make_unique<helpers::DirectoryFinder>(
          ipc_server_runner::kSessionDataDirectory,
          helpers::DirectoryFinder::ReferenceFrame::RelativeToExec);

  // Construction - TemplateRecognitionInterface
  std::unique_ptr<template_recognition::TemplateRecognitionInterface>
      template_recognition_interface =
          std::make_unique<template_recognition::SimpleRecognition>();

  // Construction - ImageCommandDispatcher
  std::unique_ptr<ipc::FileManager> file_manager =
      std::make_unique<ipc::FileManager>();
  std::unique_ptr<ipc::ipc_server::ImageCommandDispatcher>
      image_command_dispatcher =
          std::make_unique<ipc::ipc_server::ImageCommandDispatcher>(
              session_directory_.get(), file_manager.get(),
              template_recognition_interface.get());

  // Construction - ImageCommandCreator
  std::unique_ptr<postal_service::PostCardQueue> response_handler =
      std::make_unique<postal_service::PostCardQueue>();
  std::unique_ptr<ipc::ipc_server::ImageCommandCreator> image_command_creator =
      std::make_unique<ipc::ipc_server::ImageCommandCreator>(
          image_command_dispatcher.get(), response_handler.get());

  // Construction - IpcServerController
  std::unique_ptr<ipc::ipc_server::IpcServerController> ipc_server_controller =
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
