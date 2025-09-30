#include "server_clientData.h"

ClientData::ClientData(int id, Socket&& socket, Queue<std::string>& queue)
    : id(id), socket(std::move(socket)), serverQueue(queue) ,
    senderThread(nullptr), receiverThread(nullptr), nitroTime(0) {}

void ClientData::startThreads() {
    senderThread = std::make_unique<SenderThread>(&socket);
    senderThread->start();

    receiverThread = std::make_unique<ReceiverThread>(&socket, serverQueue, nitroTime);
    receiverThread->start();
}

void ClientData::shutdown() {
    socket.shutdown(SHUT_RDWR);
    socket.close();

    if (senderThread) {
        // std::cout << "DEBUG: SenderThread disconnected" << std::endl;
        senderThread->join();
        senderThread = nullptr;
    }

    if (receiverThread) {
        // std::cout << "DEBUG: ReceiverThread disconnected" << std::endl;
        receiverThread->join();
        receiverThread = nullptr;
    }
}

void ClientData::activateNitro() {
    if (nitroTime == 0) {
        nitroTime = Constants::NITRO_TIME_ITERATIONS;
    }
}

bool ClientData::nitroEnded() {
    if (nitroTime == 0) return false;
    nitroTime--;
    return nitroTime == 0;
}
