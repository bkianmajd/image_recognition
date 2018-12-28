#include "libraries/postal_service/com_layer/client/tcp_client.h"
#include "libraries/postal_service/com_layer/com_defs.h"
#include "libraries/postal_service/com_layer/server/tcp_server.h"

#include <stdlib.h>
#include <QCoreApplication>
#include <QTcpSocket>
#include <iostream>
#include <thread>

#include "gtest/gtest.h"

using namespace com_layer;
// https://gist.github.com/TheBuzzSaw/5889632
// http://www.bogotobogo.com/Qt/Qt5_QTcpServer_Client_Server.php

void Quit(QCoreApplication* a, int seconds) {
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
  a->quit();
}

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  TcpServer tcp_server_;
  TcpClient tcp_client_;
  ConnectionInfo connection_info;

  tcp_server_.Init(connection_info);

  qDebug() << "starting to connect\n";
  tcp_client_.Init(connection_info);

  auto t1 = std::thread(Quit, &a, 1);
  a.exec();
  t1.join();

  return 0;
}
