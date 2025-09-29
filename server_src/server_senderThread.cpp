#include "server_senderThread.h"

SenderThread::SenderThread(Socket* socket) :
    socket(socket), keepRunning(true) {}

void SenderThread::run() {
    std::cout << "Sender Thread Started" << std::endl;
}
