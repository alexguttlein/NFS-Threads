#include "server_class.h"

Server::Server(const char* port) :
    monitorClients(),
    messagesQueue(Constants::SERVER_QUEUE_MAXSIZE),
    acceptor(port, monitorClients, messagesQueue),
    gameloop(messagesQueue, monitorClients) {}

void Server::run() {

    // se inicia el thread aceptador
    acceptor.start();

    // se inicia el gameloop
    gameloop.start();

    std::string end;
    while (true) {
        std::getline(std::cin, end);
        if (end == "q") break;
    }

    closeGameLoop();
    closeAcceptor();
    closeClients();

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
