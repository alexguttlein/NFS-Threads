#ifndef SERVER_SENDERTHREAD_H
#define SERVER_SENDERTHREAD_H
#include "../common_src/common_socket.h"
#include "../common_src/common_thread.h"
#include "../common_src/common_queue.h"
#include "../common_src/common_constants.h"

class SenderThread : public Thread {
public:
    SenderThread(Socket* socket, Queue<uint8_t>* clientQueue);
    void run() override;

private:
    Socket* socket;
    bool keepRunning;
    Queue<uint8_t>* clientQueue;
};

#endif  // SERVER_SENDERTHREAD_H
