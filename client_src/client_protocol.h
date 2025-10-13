#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>

#include <arpa/inet.h>

#include "../common_src/common_constants.h"
#include "../common_src/common_message.h"
#include "../common_src/common_socket.h"

class ClientProtocol {
public:
    ClientProtocol(const char* host, const char* port);
    void sendNitro();
    std::string readMsg();
    ~ClientProtocol();

private:
    Socket socket;
    bool isClosed;
};

#endif  // CLIENT_PROTOCOL_H
