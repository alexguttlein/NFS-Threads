#include "server_receiverThread.h"

#include "../common_src/common_constants.h"

ReceiverThread::ReceiverThread(Socket* socket) :
   socket(socket), keepRunning(true) {}

void ReceiverThread::run() {
    uint8_t msg;
    while (keepRunning && !socket->is_stream_recv_closed()) {
        socket->recvall(&msg, sizeof(msg));
        if (msg == Constants::CLIENT_ACTIVATE_NITRO) {
            std::cout << "NITRO ON" << std::endl;
        }
        msg = ' ';
    }
    std::cout << "ReceiverThread::run() -> SENDER CERRADO" << std::endl;
}
