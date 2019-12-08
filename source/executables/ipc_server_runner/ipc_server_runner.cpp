#include <QApplication>

#include <iostream>
#include <thread>

#include "components/image_service/server/ipc_server.h"
#include "components/menu_runner/menu_runner.h"
#include "components/session_manager/app_finder/app_finder.h"
#include "components/poker/workflow_session.h"
#include "components/session_manager/session_manager.h"
#include "executables/ipc_server_runner/static_config.h"
#include "helpers/memory_helper.hpp"
#include "libraries/session_thread/session_thread.h"

void RunMenuThread(QCoreApplication* a,
                   SessionThread<poker::WorkflowSession>* poker_session) {
  poker::MenuRunner menu_runner(poker_session);

  while (menu_runner.KeepRunning()) {
    menu_runner.ProcessUserInput();
  }
  // Signal the application to quit
  a->quit();
}

void RunSessionManagerThread(
    ipc::IpcServer* ipc_server,
    SessionThread<poker::WorkflowSession>* poker_session,
    std::atomic_bool* running) {
  running->store(true);
  // Start the session manager
  poker::SessionManager session_manager(ipc_server, poker_session);

  bool result = true;
  while (running->load() && result) {
    result = session_manager.ProcessImageServerAndPostImage();
    usleep(5);
  }

  if(result) {
    std::cerr << "Aboring! - failure" << std::endl;
  }
}

int Main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  // Construction - IpcServer
  std::unique_ptr<ipc::IpcServer> ipc_server =
      std::make_unique<ipc::IpcServer>();

  // Initialization of the IpcServer thread - has to be done on main thread
  com_layer::ConnectionInfo connection_info;
  connection_info.port = ipc_server::kPort;
  connection_info.connection_address = ipc_server::kConnectionAddress;
  ipc_server->AsyncInit(connection_info);

  // Construction - of the WorkflowSession, which runs on a SessionThread
  std::unique_ptr<SessionThread<poker::WorkflowSession>> poker_sesion =
      std::make_unique<SessionThread<poker::WorkflowSession>>();
  poker_sesion->StartSession();

  // Start the session manager thread - which runs the session manager
  std::atomic_bool running;
  std::thread t1(&RunSessionManagerThread, ipc_server.get(), poker_sesion.get(),
                 &running);

  // Start the menu thread
  std::thread t2(RunMenuThread, &a, poker_sesion.get());

  // Run the main thread in the background
  a.exec();

  // Close the threads when |a->quit()| is called
  std::cout << "Exiting" << std::endl;
  // closes the SessionManagerThread
  running.store(false);
  t2.join();
  t1.join();

  poker_sesion->EndSessionAndJoin();
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
