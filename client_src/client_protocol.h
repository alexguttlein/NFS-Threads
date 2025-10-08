#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "../common_src/common_queue.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_constants.h"

#include <string>
#include <cstdint>
#include <arpa/inet.h>
#include <iostream>
#include <ostream>

class ClientProtocol {
public:
    ClientProtocol(Queue<std::string>& clientQueue,
        const char* host, const char* port);
    // void run();
    void sendNitro();
    void readMsg(int n);
    void handleServerMessage(const std::string& msg);
    void close();
private:
    Queue<std::string>& clientQueue;
    Socket socket;
    bool isClosed;
};

#endif  // CLIENT_PROTOCOL_H
