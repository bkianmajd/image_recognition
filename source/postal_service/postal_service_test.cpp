#include "postal_service/postal_service.h"

#include <QCoreApplication>
#include <fstream>
#include <iostream>

#include "postal_service/post_cards/test_post_card.h"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  postal_service::PostalService server(postal_service::server);
  postal_service::PostalService client(postal_service::client);

  server.Init();
  client.Init();

  postal_service::Test test;
  test.value = true;
  test.x = 123;
  postal_service::TestPostCard test_post_card(test);

  client.SendPostCard(test_post_card);

  return a.exec();
  return 0;
}
