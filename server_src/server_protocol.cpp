#include "server_protocol.h"

#include <iostream>
#include <ostream>

ServerProtocol::ServerProtocol(Socket socket) : socket(std::move(socket)) {}

void ServerProtocol::sendMessage(const Message& msg) {
    if (!isConnectionClosed()) {
        socket.sendall(&msg, sizeof(msg));
    }
}

bool ServerProtocol::isConnectionClosed() const {
    return socket.is_stream_send_closed() || socket.is_stream_recv_closed();
}

uint8_t ServerProtocol::receiveMessage() {
    uint8_t msg(0);
    if (!isConnectionClosed()) {
        socket.recvall(&msg, sizeof(msg));
    }
    return msg;
}

void ServerProtocol::close() {
    try {
        socket.shutdown(SHUT_RDWR);
    } catch (const LibError& e) {
        // si ya está desconectado no vuelvo a hacerle shutdown
        std::cerr << "Socket shutdown warning: " << e.what() << std::endl;
    }
    socket.close();
}
