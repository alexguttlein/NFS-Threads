#include "server_monitorClients.h"

MonitorClients::MonitorClients() : clients(0) {}

void MonitorClients::insertClient(int id, ClientData&& client) {
    std::lock_guard<std::mutex> lock(mtx);
    clients.emplace(id, std::move(client));
}

void MonitorClients::deleteClient(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    clients.erase(id);
}

void MonitorClients::clear() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Limpiando monitor..." << std::endl;
    for (auto& [id, client] : clients) {
        std::cout << "Eliminando cliente: " << id << std::endl;
        client.shutdown();
    }
    clients.clear();
}

ClientData& MonitorClients::getClient(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    return clients.at(id); // lanza std::out_of_range si no existe
}
