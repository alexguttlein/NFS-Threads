#ifndef SERVER_CLASS_H
#define SERVER_CLASS_H

#include "server_clientData.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_queue.h"
#include "server_acceptor.h"
#include "server_monitorClients.h"
#include "server_gameLoop.h"

#include <iostream>
#include <ostream>
#include <unistd.h>
#include <string>

class Server {
public:
    explicit Server(const char* port);
    void run();
    ~Server();
private:
    MonitorClients monitorClients;
    Queue<std::string> messagesQueue;
    Acceptor acceptor;
    GameLoop gameloop;

    void closeGameLoop();
    void closeAcceptor();
    void closeClients();
};

#endif  //SERVER_CLASS_H
