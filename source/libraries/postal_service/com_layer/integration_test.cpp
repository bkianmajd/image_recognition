#include "postal_service/com_layer/com_defs.h"
#include "postal_service/com_layer/tcp_client.h"
#include "postal_service/com_layer/tcp_server.h"

#include <stdlib.h>
#include <QCoreApplication>
#include <QTcpSocket>
#include <iostream>

#include "gtest/gtest.h"

using namespace com_layer;
// https://gist.github.com/TheBuzzSaw/5889632
// http://www.bogotobogo.com/Qt/Qt5_QTcpServer_Client_Server.php

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  TcpServer tcp_server_;
  TcpClient tcp_client_;
  ConnectionInfo connection_info;

  tcp_server_.Init(connection_info);

  qDebug() << "starting to connect\n";
  tcp_client_.Init(connection_info);

  return a.exec();
}
