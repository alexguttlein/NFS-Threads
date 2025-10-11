#ifndef CLIENT_CLASS_H
#define CLIENT_CLASS_H

#include <iostream>
#include <sstream>
#include <string>

#include "../common_src/common_constants.h"
#include "../common_src/common_queue.h"
#include "client_commandDispatcher.h"
#include "client_protocol.h"

class Client {
public:
    Client(const char* host, const char* port);
    void processInput(std::string input);
    void run();
private:
    Queue<std::string> clientQueue;
    ClientProtocol protocol;
    CommandDispatcher dispatcher;
    void registerCommands();
};

#endif  //CLIENT_CLASS_H
