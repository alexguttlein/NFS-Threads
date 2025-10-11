#include "server_receiverThread.h"

ReceiverThread::ReceiverThread(ServerProtocol* serverProtocol,
    Queue<std::string>& queue, int& time) :
        serverProtocol(serverProtocol), queue(queue), keepRunning(true), time(time) {}

void ReceiverThread::run() {
    while (keepRunning) {
        uint8_t msg(0);

        if (serverProtocol->isConnectionClosed()) {
            keepRunning = false;
            return;
        }

        msg = serverProtocol->receiveMessage();

        if (msg == Constants::CLIENT_ACTIVATE_NITRO && time == 0) {
            queue.try_push(Constants::MSG_NITRO_ON);
            time = Constants::NITRO_TIME_ITERATIONS;
        }
    }
}
