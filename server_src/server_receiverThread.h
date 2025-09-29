#ifndef SERVER_RECEIVERTHREAD_H
#define SERVER_RECEIVERTHREAD_H

#include "../common_src/common_thread.h"
#include "../common_src/common_socket.h"

class ReceiverThread : public Thread {
public:
    ReceiverThread(Socket* socket);
    void run() override;
private:
    Socket* socket;
    bool keepRunning;
    void receive();
};

#endif  // SERVER_RECEIVERTHREAD_H
