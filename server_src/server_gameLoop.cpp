#include "server_gameLoop.h"

GameLoop::GameLoop(Queue<std::string>& queue, MonitorClients& clients)
    : queue(queue), clients(clients), running(false) {}

void GameLoop::run() {
    running = true;
    int nitrosActivated = 0;

    while (running) {
        clients.killDisconnectedClients();
        // si hay algo en la queue lo procesa
        std::string queueMsg;
        while (queue.try_pop(queueMsg)) {
            Message msgToBroadcast(Constants::SERVER_RESPONSE);

            nitrosActivated++;
            msgToBroadcast.addParameters(nitrosActivated, Constants::SERVER_NITRO_ACTIVATE);

            clients.broadcastToAllClients(msgToBroadcast.getMessage());
            std::cout << queueMsg << std::endl;
        }

        // si se terminó el nitro de un auto se envia a los clientes
        clients.forEachClient([this, &nitrosActivated](ClientData& client) {
                if (client.nitroEnded()) {
                    Message msgToBroadcast(Constants::SERVER_RESPONSE);
                    msgToBroadcast.addParameters(nitrosActivated,
                        Constants::SERVER_NITRO_EXPIRED);
                    nitrosActivated--;

                    clients.broadcastToAllClients(msgToBroadcast.getMessage());
                    std::cout << Constants::MSG_NITRO_OFF << std::endl;
                }
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void GameLoop::stop() {
    running = false;
}
