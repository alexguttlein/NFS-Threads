#include "server_receiverThread.h"

ReceiverThread::ReceiverThread(Socket* socket, Queue<std::string>& queue) :
   socket(socket), queue(queue), keepRunning(true) {}

void ReceiverThread::run() {
    uint8_t msg;
    while (keepRunning && !socket->is_stream_recv_closed()) {
        socket->recvall(&msg, sizeof(msg));
        if (msg == Constants::CLIENT_ACTIVATE_NITRO) {
            queue.try_push(Constants::MSG_NITRO_ON);
        }
        msg = ' ';
    }
    std::cout << "ReceiverThread::run() -> SENDER CERRADO" << std::endl;
}
