#ifndef SERVER_SENDERTHREAD_H
#define SERVER_SENDERTHREAD_H
#include "../common_src/common_socket.h"
#include "../common_src/common_thread.h"
#include "../common_src/common_queue.h"
#include "../common_src/common_constants.h"
#include "../common_src/common_message.h"

class SenderThread : public Thread {
public:
    SenderThread(Socket* socket, Queue<Msg>* clientQueue);
    void run() override;

private:
    Socket* socket;
    bool keepRunning;
    Queue<Msg>* clientQueue;
};

#endif  // SERVER_SENDERTHREAD_H
