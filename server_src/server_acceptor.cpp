#include "server_acceptor.h"

Acceptor::Acceptor(const char* port, MonitorClients& clients) :
    socket(port),
    monitorClients(clients),
    keepAccepting(true) {}

void Acceptor::run() {
    int id = 0;
    while (keepAccepting && !socket.is_stream_recv_closed()) {
        try {
            Socket newSocket = socket.accept();
            ClientData newClient{id, std::move(newSocket)};
            newClient.startThreads();

            monitorClients.insertClient(id, std::move(newClient));

            id++;
            std::cout << "Acceptor::run -> Server accepted new connection" << std::endl;
        } catch (const std::exception& e) {
            if (keepAccepting) {
                std::cerr << "Unexpected exception: " << e.what() << std::endl;
            }
            break;
        }
    }
}

void Acceptor::endAccepting() {
    keepAccepting = false;
    close();
}

void Acceptor::close() {
    this->socket.shutdown(SHUT_RDWR);
    this->socket.close();
}
