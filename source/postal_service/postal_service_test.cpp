#include "postal_service/postal_service.h"

#include <QCoreApplication>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include "postal_service/mail_distributor_simple/mail_distributor_simple.h"
#include "postal_service/post_cards/test_post_card.h"

postal_service::PostalService server(postal_service::server);
postal_service::PostalService client(postal_service::client);

void Print() {
  postal_service::MailDistributorSimple mail_distributor;
  for (int i = 0; i < 10; ++i) {
    server.GetMail(mail_distributor);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
  }
}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  server.Init();
  client.Init();

  postal_service::Test test;
  test.value = true;
  test.x = 123;
  postal_service::TestPostCard test_post_card(test);


  client.SendPostCard(test_post_card);


  std::thread t1(Print);
  return a.exec();

  t1.join();

  return 0;
}
