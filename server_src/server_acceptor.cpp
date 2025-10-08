#include "server_acceptor.h"

Acceptor::Acceptor(const char* port, MonitorClients& clients,
    Queue<std::string>& queue) :
    socket(port),
    monitorClients(clients),
    queue(queue),
    keepAccepting(true) {}

void Acceptor::run() {
    int id = 0;
    while (keepAccepting && !socket.is_stream_recv_closed()) {
        try {
            Socket newSocket = socket.accept();
            ClientData newClient{id, std::move(newSocket), queue};

            // se agrega el cliente a la lista de clientes
            monitorClients.insertClient(id, std::move(newClient));

            //se busca al cliente y se inicializan los threads
            // ClientData& clientInMap = monitorClients.getClient(id);
            // clientInMap.startThreads();
            monitorClients.forClient(id, [](ClientData& c) {
                c.startThreads();
            });

            id++;
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
