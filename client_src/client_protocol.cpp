#include "client_protocol.h"

ClientProtocol::ClientProtocol(Queue<std::string>& clientQueue,
    const char* host, const char* port) :
    clientQueue(clientQueue),
    socket(host, port),
    isClosed(false) {}

void ClientProtocol::run() {
    std::cout << "Running protocol..." << std::endl;
    close();
}

void ClientProtocol::sendNitro() {
    uint8_t msg = Constants::CLIENT_ACTIVATE_NITRO;
    socket.sendall(&msg, sizeof(msg));
    std::cout << "Nitro enviado" << std::endl;
}

void ClientProtocol::readMsg(int n) {
    std::cout << "Reading " << n << std::endl;
}

void ClientProtocol::handleServerMessage(const std::string& msg) {
    clientQueue.push(msg);
}

void ClientProtocol::close() {
    std::cout << "Closing client socket..." << std::endl;
    if (!socket.is_stream_recv_closed()) {
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
    }
}
