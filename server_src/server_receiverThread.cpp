#include "server_receiverThread.h"

ReceiverThread::ReceiverThread(Socket* socket, Queue<std::string>& queue, int& time) :
   socket(socket), queue(queue), keepRunning(true), time(time) {}

void ReceiverThread::run() {
    while (keepRunning) {
        uint8_t msg(0);

        if (socket->is_stream_recv_closed() || socket->is_stream_send_closed()) {
            keepRunning = false;
            return;
        }

        socket->recvall(&msg, sizeof(msg));

        if (msg == Constants::CLIENT_ACTIVATE_NITRO && time == 0) {
            queue.try_push(Constants::MSG_NITRO_ON);
            time = Constants::NITRO_TIME_ITERATIONS;
        }
    }
}
