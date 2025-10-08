#include "client_protocol.h"

ClientProtocol::ClientProtocol(Queue<std::string>& clientQueue,
    const char* host, const char* port) :
    clientQueue(clientQueue),
    socket(host, port),
    isClosed(false) {}

void ClientProtocol::sendNitro() {
    uint8_t msg = Constants::CLIENT_ACTIVATE_NITRO;
    socket.sendall(&msg, sizeof(msg));
    // std::cout << "DEBUG: Nitro enviado" << std::endl;
}

void ClientProtocol::readMsg(int n) {
    // std::cout << "DEBUG: Reading " << n << std::endl;
    uint8_t msg;
    std::string msgQueue;
    for (int i = 0; i < n; i++) {
        if (socket.is_stream_recv_closed() || socket.is_stream_send_closed())
            return;
        socket.recvall(&msg, sizeof(msg));

        if (msg == Constants::SERVER_NITRO_ACTIVATE) {
            msgQueue = Constants::MSG_NITRO_ON;
        } else if (msg == Constants::SERVER_NITRO_EXPIRED) {
            msgQueue = Constants::MSG_NITRO_OFF;
        }
        clientQueue.push(msgQueue);
    }
}

void ClientProtocol::close() {
    // std::cout << "DEBUG: Closing client socket..." << std::endl;
    if (!socket.is_stream_recv_closed()) {
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
    }
}
