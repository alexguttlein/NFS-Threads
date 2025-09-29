#include "server_receiverThread.h"

ReceiverThread::ReceiverThread(Socket& socket) :
   socket(socket), keepRunning(true) {}

void ReceiverThread::run() {
    std::cout << "Receiver Thread Started" << std::endl;
}

