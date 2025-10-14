#include "server_class.h"

Server::Server(const char* port) :
    monitorClients(),
    messagesQueue(Constants::SERVER_QUEUE_MAXSIZE),
    acceptor(port, monitorClients, messagesQueue),
    gameloop(messagesQueue, monitorClients) {

    acceptor.start();
    gameloop.start();
}

void Server::run() {
    std::string end;
    while (std::getline(std::cin, end)) {
        if (end == "q") break;
    }
}

void Server::closeAcceptor() {
    acceptor.endAccepting();
}

void Server::closeClients() {
    monitorClients.clear();
}

void Server::closeGameLoop() {
    gameloop.stop();
    gameloop.join();
}

Server::~Server() {
    closeGameLoop();
    closeAcceptor();
    closeClients();
}
