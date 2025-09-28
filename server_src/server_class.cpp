#include "server_class.h"

#include <iostream>
#include <ostream>

#include <unistd.h>

Server::Server(const char* port) :
    clients(),
    acceptor(port, clients) {}

void Server::run() {
    std::cout << "Server starting..." << std::endl;

    // se inicia el thread aceptador
    acceptor.start();

    int time = 0;
    while (time < 5) {
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
    for (auto& [id, client] : clients) {
        client.shutdown();
    }
    clients.clear();
}
