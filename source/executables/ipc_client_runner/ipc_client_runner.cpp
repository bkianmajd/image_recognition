#include <QApplication>

#include <iostream>
#include <thread>

#include "components/image_service/client/ipc_client.h"
#include "executables/ipc_client_runner/static_config.h"
#include "helpers/memory_helper.hpp"
#include "libraries/postal_service/com_layer/com_defs.h"
#include "libraries/postal_service/postal_service.h"
#include "libraries/screenshot_creator/screenshot_creator.h"

const std::string kImageName = "screenshot.jpg";
const std::chrono::seconds kScreenshonFrequency = std::chrono::seconds(10);

void RunControllerThread(
    QCoreApplication* a, ipc::IpcClient* ipc_client,
    template_recognition::ScreenshotCreator* screenshot_creator) {
  auto start_time = std::chrono::system_clock::now();
  while (!ipc_client->IsInit()) {
    if (std::chrono::system_clock::now() - start_time > ipc_client::kTimeout) {
      std::cerr << "Could not initialize ipc client" << std::endl;
      a->quit();
      return;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  bool run_mode = true;

  while (run_mode) {
    // Takes a screenshot of the desktop
    if (!screenshot_creator->Capture()) {
      std::cerr << "Capture failed" << std::endl;
      break;
    }

    // Sends the image to the server
    std::vector<char> bytes = screenshot_creator->GetLastCapture();
    std::cout << "sending bytes: " << bytes.size() << std::endl;
    if (!ipc_client->SendImage(bytes, kImageName)) {
      std::cerr << "Failed to send image" << std::endl;
      break;
    }

    std::this_thread::sleep_for(kScreenshonFrequency);
  }

  std::cout << "Stopping running thread" << std::endl;
  a->quit();
}

int Main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  // Construction - IpcClient
  std::unique_ptr<ipc::IpcClient> ipc_client =
      std::make_unique<ipc::IpcClient>();

  std::unique_ptr<template_recognition::ScreenshotCreator> screenshot_creator =
      std::make_unique<template_recognition::ScreenshotCreator>();

  // Init communication - must be called within this thread
  com_layer::ConnectionInfo connection_info;
  connection_info.port = ipc_client::kPort;
  connection_info.connection_address = ipc_client::kConnectionAddress;
  ipc_client->AsyncInit(connection_info);

  // Start thread and transfer ownership
  std::thread t1(RunControllerThread, &a, ipc_client.get(),
                 screenshot_creator.get());

  // Run the main thread in the background
  a.exec();

  std::cout << "Closing threads" << std::endl;
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
