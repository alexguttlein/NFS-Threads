#include "server_class.h"

#include <iostream>
#include <ostream>

#include <unistd.h>

Server::Server(const char* port) :
    monitorClients(),
    acceptor(port, monitorClients) {}

void Server::run() {
    std::cout << "Server starting..." << std::endl;

    // se inicia el thread aceptador
    acceptor.start();

    int time = 0;
    while (time < 10) {
        sleep(1);
        time++;
    }

    closeAcceptor();
    closeClients();

    std::cout << "Server ending..." << std::endl;
}

void Server::closeAcceptor() {
    acceptor.endAccepting();
    acceptor.join();
}

void Server::closeClients() {
    monitorClients.clear();
}
