#include <QCoreApplication>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include "google_test/testing_def.h"
#include "helpers/directory_finder.h"
#include "helpers/memory_helper.hpp"
#include "image_ipc/file_manager/file_manager.h"
#include "image_ipc/ipc_server/response_handler.h"
#include "postal_service/post_cards/test_post_card.h"
#include "postal_service/postal_service.h"
#include "schema/compiled_files/template_match.pb.h"

postal_service::PostalService client(postal_service::client);
ipc::ipc_server::ResponseHandler response_handler;

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
      testing_main::kTestingDirectoryFromWorkspace,
      helpers::DirectoryFinder::ReferenceFrame::RelativeToWorkspace);

  // Get the binary of the file image
  ipc::ipc_server::FileManager file_manager(directory_finder.GetAbsPath());
  std::vector<char> binary = file_manager.ReadFile(testing_main::kImageOne);

  std::cout << "Storing image of size " << binary.size() << std::endl;

  // Create the proto file
  // todo make this a general proto_any_handler_
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
  // TODO() Write a mail distributor mailbox
  // mail distributor queue
  // client.GetMail();

  // a->quit();
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
