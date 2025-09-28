#include "server_acceptor.h"

Acceptor::Acceptor(const char* port, std::unordered_map<int, ClientData>& clients) :
    socket(port),
    clients(clients),
    keepAccepting(true) {}

void Acceptor::run() {
    int id = 0;
    while (keepAccepting && !socket.is_stream_recv_closed()) {
        try {
            Socket newSocket = socket.accept();
            ClientData cd{id, std::move(newSocket)};
            clients.emplace(cd.id, std::move(cd));
            id++;
            std::cout << "Server accepted new connection" << std::endl;
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
