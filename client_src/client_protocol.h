#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>

#include <arpa/inet.h>

#include "../common_src/common_constants.h"
#include "../common_src/common_message.h"
#include "../common_src/common_queue.h"
#include "../common_src/common_socket.h"

class ClientProtocol {
public:
    ClientProtocol(Queue<std::string>& clientQueue,
        const char* host, const char* port);
    void sendNitro();
    void readMsg(int n);
    void close();
private:
    Queue<std::string>& clientQueue;
    Socket socket;
    bool isClosed;
};

#endif  // CLIENT_PROTOCOL_H
