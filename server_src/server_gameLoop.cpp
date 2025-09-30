#include "server_gameLoop.h"

GameLoop::GameLoop(Queue<std::string>& queue, MonitorClients& clients)
    : queue(queue), clients(clients), running(false) {}

void GameLoop::run() {
    running = true;

    while (running) {
        // si hay algo en la queue lo procesa
        std::string msg;
        if (queue.try_pop(msg)) {
            // broadcastToAllClients(Constants::msg);
            std::cout << msg << std::endl;
        }

        // si se terminó el nitro de un auto se envia a los clientes
        clients.forEachClient([](ClientData& client) {
                if (client.nitroEnded()) {
                    // broadcastToAllClients(Constants::MSG_NITRO_OFF)
                    std::cout << Constants::MSG_NITRO_OFF << std::endl;
                }
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void GameLoop::stop() {
    running = false;
}
