#ifndef SERVER_RECEIVERTHREAD_H
#define SERVER_RECEIVERTHREAD_H

#include "../common_src/common_socket.h"
#include "../common_src/common_thread.h"
#include "../common_src/common_constants.h"
#include "../common_src/common_queue.h"

class ReceiverThread : public Thread {
public:
    // ReceiverThread(Socket* socket);
    ReceiverThread(Socket* socket, Queue<std::string>& queue);
    void run() override;
private:
    Socket* socket;
    Queue<std::string>& queue;
    bool keepRunning;
    void receive();
};

#endif  // SERVER_RECEIVERTHREAD_H
