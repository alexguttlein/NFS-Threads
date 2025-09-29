#ifndef SERVER_CLASS_H
#define SERVER_CLASS_H

#include <unordered_map>

#include "../common_src/common_clientData.h"
#include "../common_src/common_socket.h"

#include "MonitorClients.h"
#include "server_acceptor.h"
#include "server_protocol.h"

class Server {
public:
    Server(const char* port);
    void run();
private:
    // ServerProtocol protocol;
    // std::unordered_map<int, ClientData> clients;
    MonitorClients monitorClients;
    Acceptor acceptor;
    void closeAcceptor();
    void closeClients();
};

#endif  //SERVER_CLASS_H
