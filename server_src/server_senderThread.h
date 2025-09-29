#ifndef SERVER_SENDERTHREAD_H
#define SERVER_SENDERTHREAD_H
#include "../common_src/common_socket.h"

#include "../common_src/common_thread.h"

class SenderThread : public Thread {
public:
    SenderThread(Socket& socket);
    void run() override;
private:
    Socket& socket;
    bool keepRunning;
};

#endif  // SERVER_SENDERTHREAD_H
