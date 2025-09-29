#include "server_class.h"

#include <iostream>
#include <ostream>
#include <unistd.h>

#include <chrono>
#include <thread>


Server::Server(const char* port) :
    monitorClients(),
    messagesQueue(Constants::SERVER_QUEUE_MAXSIZE),
    acceptor(port, monitorClients, messagesQueue) {}

void Server::run() {
    std::cout << "Server starting..." << std::endl;

    // se inicia el thread aceptador
    acceptor.start();

    float time = 0;
    // gameloop
    while (time < 15) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        time += 0.25;
    }
    std::string msg;
    messagesQueue.try_pop(msg);
    if (!msg.empty()) std::cout << "pop: " << msg << std::endl;

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
