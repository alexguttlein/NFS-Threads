#ifndef SERVER_CLASS_H
#define SERVER_CLASS_H

#include "../common_src/common_socket.h"
#include "../common_src/common_clientData.h"
#include "server_acceptor.h"
#include "server_protocol.h"

#include <unordered_map>

class Server {
public:
    Server(const char* port);
    void run();
private:
    // ServerProtocol protocol;
    std::unordered_map<int, ClientData> clients;
    Acceptor acceptor;
    void closeAcceptor();
    void closeClients();
};

#endif  //SERVER_CLASS_H
