#include "postal_service/postal_service.h"

#include <QCoreApplication>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include "postal_service/utility/mail_distributor_simple.h"
#include "postal_service/utility/test_post_card.h"

postal_service::PostalService server(postal_service::server);
postal_service::PostalService client(postal_service::client);

void Print(QCoreApplication* a) {
  client.WaitForOpen();

  std::cout << "Sending info\n";
  std::flush(std::cout);

  // Sending stuff from a different thread from client
  postal_service::Test test;
  test.value = true;
  test.x = 123;
  postal_service::TestPostCard test_post_card(test);
  client.SendPostCard(test_post_card);

  postal_service::MailDistributorSimple mail_distributor;
  for (int i = 0; i < 2; ++i) {
    server.GetMail(mail_distributor);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
  }

  // Sending stuff from a different thread from server
  server.SendPostCard(test_post_card);

  a->quit();
}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  com_layer::ConnectionInfo connection_info;
  server.AsyncInit(connection_info);
  client.AsyncInit(connection_info);



  std::thread t1(Print, &a);
  a.exec();

  t1.join();

  return 0;
}
