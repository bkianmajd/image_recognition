#include <QCoreApplication>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include "google_test/testing_def.h"
#include "helpers/directory_finder.h"
#include "helpers/memory_helper.hpp"
#include "helpers/file_manager.h"
#include "postal_service/postal_service.h"
#include "postal_service/utility/mail_distributor_queue.h"
#include "postal_service/utility/post_card_queue.h"
#include "schema/compiled_files/image_request_response_commands.pb.h"

postal_service::PostalService client(postal_service::client);
postal_service::PostCardQueue response_handler;

void StartClient(QCoreApplication* a) {
  if (!client.WaitForOpen()) {
    std::cout << "timeout failed to connect" << std::endl;
    a->quit();
  }

  std::cout << "Connection success!" << std::endl;
  std::flush(std::cout);

  // Run the application by sending a few post cards

  // Get a single image from the kTestingDirectory
  helpers::DirectoryFinder directory_finder(
      tester::kTestingDirectoryFromWorkspace,
      helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace);

  // Get the binary of the file image
  ipc::FileManager file_manager;
  std::vector<char> binary = file_manager.ReadFile(
      directory_finder.GetAbsPathOfTargetFile(tester::kImageOne));

  std::cout << "Storing image of size " << binary.size() << std::endl;

  // Create the proto file
  std::unique_ptr<ipc_interface::StoreImageRequest> request =
      std::make_unique<ipc_interface::StoreImageRequest>();

  std::string* str = request->mutable_image();
  str->append(binary.begin(), binary.end());
  request->mutable_image_name()->append("testImage.jpg");
  std::cout << "request image size: " << request->ByteSize() << std::endl;

  // For now we use the response handler to handle this any message
  response_handler.Push(std::move(request));

  // Send the proto file
  client.SendPostCard(response_handler);

  // Wait for the response
  postal_service::MailDistributorQueue response_queue;
  while (response_queue.Empty()) {
    client.GetMail(response_queue);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  auto test = response_queue.Front();
  test.PrintDebugString();

  a->quit();
}

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  com_layer::ConnectionInfo connection_info;
  client.AsyncInit(connection_info);

  std::thread t1(StartClient, &a);
  a.exec();

  t1.join();

  return 0;
}
