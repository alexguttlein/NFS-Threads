#include "client_protocol.h"

ClientProtocol::ClientProtocol(const char* host, const char* port) :
    socket(host, port),
    isClosed(false) {}

void ClientProtocol::sendNitro() {
    uint8_t msg = Constants::CLIENT_ACTIVATE_NITRO;
    socket.sendall(&msg, sizeof(msg));
}

std::string ClientProtocol::readMsg() {
    Message msg;
    std::string response;

    if (socket.is_stream_recv_closed() || socket.is_stream_send_closed())
        return "";
    socket.recvall(&msg, sizeof(msg));

    if (msg.type == Constants::SERVER_NITRO_ACTIVATE) {
        response = Constants::MSG_NITRO_ON;
    } else if (msg.type == Constants::SERVER_NITRO_EXPIRED) {
        response = Constants::MSG_NITRO_OFF;
    }

    return response;
}

ClientProtocol::~ClientProtocol() {
    if (!isClosed && !socket.is_stream_recv_closed()) {
        socket.shutdown(SHUT_RDWR);
        socket.close();
        isClosed = true;
    }
}
