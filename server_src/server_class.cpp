#include "server_class.h"

#include <iostream>
#include <ostream>
#include <unistd.h>

#include <chrono>
#include <thread>


Server::Server(const char* port) :
    monitorClients(),
    acceptor(port, monitorClients) {}

void Server::run() {
    std::cout << "Server starting..." << std::endl;

    // se inicia el thread aceptador
    acceptor.start();

    float time = 0;
    // gameloop
    while (time < 45) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        time += 0.25;
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
