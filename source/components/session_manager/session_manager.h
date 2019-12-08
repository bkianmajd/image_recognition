#ifndef SESSION_MANAGER_H_
#define SESSION_MANAGER_H_

#include "components/image_service/server/ipc_server.h"
#include "components/poker/workflow_session.h"
#include "components/session_manager/app_finder/app_finder.h"
#include "libraries/session_thread/session_thread.h"

namespace poker {

class SessionManager {
 public:
  SessionManager(ipc::IpcServer* ipc_server,
                 SessionThread<WorkflowSession>* session)
      : ipc_server_(ipc_server), default_session_(session) {}

  /// polls the image server, needs to be called frequently
  bool ProcessImageServerAndPostImage() {
    if (!ipc_server_) {
      std::cerr << "Cannot run - ipc server is a nullptr;" << std::endl;
      return false;
    }

    // Server is not started - wait for next cycle
    if (!ipc_server_->IsInit()) {
      usleep(100);
      return true;
    }

    // Handle this error by returning false
    int client_identifier = 0;
    if (!ipc_server_->CheckForImage(&client_identifier, &image_bytes_)) {
      return false;
    }

    // TODO(BK): Handle the client identifier by creating a new session

    // Check the server for an image in the queue
    image::Image image = app_finder_.Narrow(image_bytes_);
    if (image.empty()) {
      // Empty - sleep for some time
      usleep(500);
      return true;
    }

    default_session_->task_runner()->PostTask(
        FROM_HERE,
        base::Bind(&WorkflowSession::ProcessImage,
                   base::Unretained(default_session_->get()), image));
    // TODO(BK): Send a response to server

    return true;
  }

 private:
  // Dependency injected
  ipc::IpcServer* ipc_server_;
  SessionThread<WorkflowSession>* default_session_;

  std::vector<char> image_bytes_;
  AppFinder app_finder_;
};

}  // namespace poker

#endif  // SESSION_MANAGER_H_
