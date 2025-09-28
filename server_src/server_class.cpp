#include "server_class.h"

#include <iostream>
#include <ostream>

Server::Server(const char* port) : port(port) {}

void Server::run() {
    std::cout << "Server starting..." << std::endl;
}

