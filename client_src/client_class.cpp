#include "client_class.h"

#include <iostream>
#include <ostream>

Client::Client(const char* host, const char* port) : port(port), host(host) { }

void Client::run() {
    std::cout << "Running client..." << std::endl;

}
