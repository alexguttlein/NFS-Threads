#include "server_gameLoop.h"

GameLoop::GameLoop(Queue<std::string>& queue, MonitorClients& clients)
    : queue(queue), clients(clients), running(false) {}

void GameLoop::run() {
    running = true;

    while (running) {
        // si hay algo en la queue lo procesa
        std::string msg;
        while (queue.try_pop(msg)) {
            clients.broadcastToAllClients(Constants::SERVER_NITRO_ACTIVATE);
            std::cout << msg << std::endl;
        }

        // si se terminó el nitro de un auto se envia a los clientes
        clients.forEachClient([this](ClientData& client) {
                if (client.nitroEnded()) {
                    std::cout << Constants::MSG_NITRO_OFF << std::endl;
                    clients.broadcastToAllClients(Constants::SERVER_NITRO_EXPIRED);

                }
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void GameLoop::stop() {
    running = false;
}
