#ifndef SERVER_SENDERTHREAD_H
#define SERVER_SENDERTHREAD_H
#include "../common_src/common_constants.h"
#include "../common_src/common_message.h"
#include "../common_src/common_queue.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_thread.h"
#include "server_protocol.h"

class SenderThread : public Thread {
public:
    SenderThread(ServerProtocol* serverProtocol, Queue<Message>* clientQueue);
    void run() override;

private:
    ServerProtocol* serverProtocol;
    bool keepRunning;
    Queue<Message>* clientQueue;
};

#endif  // SERVER_SENDERTHREAD_H
