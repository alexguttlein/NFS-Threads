#include "server_clientData.h"
#include "../common_src/common_liberror.h"

ClientData::ClientData(int id, Socket&& socket, Queue<std::string>& queue)
    : id(id), socket(std::move(socket)), serverQueue(queue) ,
    senderThread(nullptr), receiverThread(nullptr), nitroTime(0),
    clientQueue(std::make_unique<Queue<Msg>>(Constants::CLIENT_QUEUE_MAXSIZE)) {}

void ClientData::startThreads() {
    senderThread = std::make_unique<SenderThread>(&socket, clientQueue.get());
    senderThread->start();

    receiverThread = std::make_unique<ReceiverThread>(&socket, serverQueue, nitroTime);
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
        if (!socket.is_stream_recv_closed() && !socket.is_stream_send_closed()) {
            try {
                socket.shutdown(SHUT_RDWR);
            } catch (const LibError& e) {
                // si ya está desconectado no vuelvo a hacerle shutdown
                std::cerr << "Socket shutdown warning: " << e.what() << std::endl;
            }
            socket.close();
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

void ClientData::enqueueMessage(const Msg& msg) {
    clientQueue->try_push(msg);
}

bool ClientData::isConnected() const {
    return !socket.is_stream_recv_closed() && !socket.is_stream_send_closed();
}
