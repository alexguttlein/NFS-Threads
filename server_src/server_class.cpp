#include "server_class.h"

Server::Server(const char* port) :
    monitorClients(),
    messagesQueue(Constants::SERVER_QUEUE_MAXSIZE),
    acceptor(port, monitorClients, messagesQueue),
    gameloop(messagesQueue, monitorClients) {}

void Server::run() {
    std::cout << "Server starting..." << std::endl;

    // se inicia el thread aceptador
    acceptor.start();
    gameloop.start();

    std::string end;
    while (true) {
        std::getline(std::cin, end);
        if (end == "q") break;
    }

    closeGameLoop();
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

void Server::closeGameLoop() {
    gameloop.stop();
    gameloop.join();
}
