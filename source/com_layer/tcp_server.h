#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <QtGlobal>
#include <QTcpServer>
#include <QTcpSocket>
#include <mutex>

namespace com_layer {

class TcpServer : public QObject {
  Q_OBJECT
public:
  TcpServer();

  void StartListening();

private slots:
  void OnNewConnection();

  // the |tcp_socket_| has sent a signal ReadyRead
  // and the tcp socket is ready to read data from the socket.
  void OnReadyRead();

private:
  QTcpServer tcp_server_;
  QTcpSocket* tcp_socket_;
  QByteArray byte_array_;

  std::mutex mutex;
};

}  // namespace com_layer

#endif  // TCP_SERVER_H_
