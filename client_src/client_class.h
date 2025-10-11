#ifndef CLIENT_CLASS_H
#define CLIENT_CLASS_H

#include "../common_src/common_queue.h"
#include "../common_src/common_constants.h"
#include "client_protocol.h"

#include <iostream>
#include <string>
#include <sstream>

class Client {
public:
    Client(const char* host, const char* port);
    void processInput(std::string input);
    void run();
private:
    Queue<std::string> clientQueue;
    ClientProtocol protocol;
};

#endif  //CLIENT_CLASS_H
