#include "server_gameLoop.h"

GameLoop::GameLoop(Queue<std::string>& queue, MonitorClients& clients)
    : queue(queue), clients(clients), running(false) {}

void GameLoop::run() {
    running = true;
    int nitrosActivated = 0;

    while (running) {
        // si algun cliente se deconectó lo elimino
        clients.killDisconnectedClients();

        // si la queue tiene mensajes los envio a los clientes
        unqueueAndBroadcastMsg(nitrosActivated);

        // si algun nitro expiro se envia a los clientes
        checkNitroExpirationAndBroadcast(nitrosActivated);

        std::this_thread::sleep_for(std::chrono::milliseconds(Constants::THREAD_SLEEP_MS));
    }
}

void GameLoop::unqueueAndBroadcastMsg(int& nitrosActivated) {
    // si hay algo en la queue lo procesa
    std::string queueMsg;
    while (queue.try_pop(queueMsg)) {
        MessageBuilder msgToBroadcast(Constants::SERVER_RESPONSE);

        nitrosActivated++;
        msgToBroadcast.addParameters(nitrosActivated, Constants::SERVER_NITRO_ACTIVATE);

        // se envia mensaje a todos los clientes
        clients.broadcastToAllClients(msgToBroadcast.getMessage());
        std::cout << queueMsg << std::endl;
    }
}

void GameLoop::checkNitroExpirationAndBroadcast(int& nitrosActivated) {
    // si se terminó el nitro de un auto se envia a los clientes
    clients.forEachClient([this, &nitrosActivated](ClientData& client) {
        if (client.nitroEnded()) {
            nitrosActivated--;

            MessageBuilder msgToBroadcast(Constants::SERVER_RESPONSE);
            msgToBroadcast.addParameters(nitrosActivated, Constants::SERVER_NITRO_EXPIRED);

            clients.broadcastToAllClients(msgToBroadcast.getMessage());
            std::cout << Constants::MSG_NITRO_OFF << std::endl;
        }
    });
}

void GameLoop::stop() {
    running = false;
}
