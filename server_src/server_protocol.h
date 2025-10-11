#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "../common_src/common_socket.h"
#include "../common_src/common_message.h"
#include "../common_src/common_liberror.h"

#include <cstdint>
#include <arpa/inet.h>

class ServerProtocol {
public:
    explicit ServerProtocol(Socket socket);
    void sendMessage(const Message& msg);
    uint8_t receiveMessage();
    bool isConnectionClosed() const;
    void close();

private:
    Socket socket;
};

#endif  // SERVER_PROTOCOL_H
