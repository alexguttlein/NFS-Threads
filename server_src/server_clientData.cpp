#include "server_clientData.h"

ClientData::ClientData(int id, Socket&& socket, Queue<std::string>& queue) :
    id(id), serverProtocol(std::move(socket)), serverQueue(queue) ,
    senderThread(nullptr), receiverThread(nullptr), nitroTime(0),
    clientQueue(std::make_unique<Queue<Message>>(Constants::CLIENT_QUEUE_MAXSIZE)) {}

void ClientData::startThreads() {
    senderThread = std::make_unique<SenderThread>(&serverProtocol, clientQueue.get());
    senderThread->start();

    receiverThread = std::make_unique<ReceiverThread>(&serverProtocol, serverQueue, nitroTime);
    receiverThread->start();
}

void ClientData::shutdown() {

    try {
        clientQueue->close();

        if (senderThread) {
            senderThread->join();
            senderThread = nullptr;
        }

        if (receiverThread) {
            receiverThread->join();
            receiverThread = nullptr;
        }

        // 3️⃣ Recién ahora cerrás el socket
        if (!serverProtocol.isConnectionClosed()) {
            serverProtocol.close();
        }
    } catch (const std::exception& e) {
        std::cerr << "ClientData::shutdown exception: " << e.what() << std::endl;
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

void ClientData::enqueueMessage(const Message& msg) {
    clientQueue->try_push(msg);
}

bool ClientData::isConnected() const {
    return !serverProtocol.isConnectionClosed();
}
