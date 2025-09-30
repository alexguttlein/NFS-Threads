#ifndef SERVER_RECEIVERTHREAD_H
#define SERVER_RECEIVERTHREAD_H

#include "../common_src/common_socket.h"
#include "../common_src/common_thread.h"
#include "../common_src/common_constants.h"
#include "../common_src/common_queue.h"

#include <string>

class ReceiverThread : public Thread {
public:
    // ReceiverThread(Socket* socket);
    ReceiverThread(Socket* socket, Queue<std::string>& queue, int& time);
    void run() override;
private:
    Socket* socket;
    Queue<std::string>& queue;
    bool keepRunning;
    int& time;
};

#endif  // SERVER_RECEIVERTHREAD_H
