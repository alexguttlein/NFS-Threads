#include "server_acceptor.h"

Acceptor::Acceptor(const char* port, MonitorClients& clients,
    Queue<std::string>& queue) :
    socket(port),
    monitorClients(clients),
    queue(queue),
    keepAccepting(true) {}

void Acceptor::run() {
    int id = 0;
    while (keepAccepting) {
        try {
            // se acepta un nuevo cliente
            Socket newSocket = socket.accept();
            ClientData newClient{id, std::move(newSocket), queue};

            // se agrega a la lista de clientes y se inician sus hilos
            addNewClient(id, std::move(newClient));

            id++;
        } catch (const std::exception& e) {
            if (keepAccepting) {
                std::cerr << "Unexpected exception: " << e.what() << std::endl;
            }
            break;
        }
    }
}

void Acceptor::addNewClient(int id, ClientData newClient) {
    // se agrega el cliente a la lista de clientes
    monitorClients.insertClient(id, std::move(newClient));

    // se busca al cliente y se inicializan los threads
    monitorClients.forClient(id, [](ClientData& c) {
        c.startThreads();
    });
}

void Acceptor::endAccepting() {
    keepAccepting = false;
    closeSocket();
}

Acceptor::~Acceptor() {
    endAccepting();
    if (this->Thread::is_alive()) {
        this->Thread::join();
    }
}

void Acceptor::closeSocket() {
    if (!socket.is_stream_recv_closed() && !socket.is_stream_send_closed()) {
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
    }
}
