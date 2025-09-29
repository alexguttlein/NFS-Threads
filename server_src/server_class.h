#ifndef SERVER_CLASS_H
#define SERVER_CLASS_H

#include "server_clientData.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_queue.h"
#include "server_acceptor.h"
#include "server_monitorClients.h"

class Server {
public:
    Server(const char* port);
    void run();
private:
    MonitorClients monitorClients;
    Queue<std::string> messagesQueue;
    Acceptor acceptor;
    void closeAcceptor();
    void closeClients();
};

#endif  //SERVER_CLASS_H
