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
    for (auto& [id, client] : clients) {
        client.shutdown();
    }
    clients.clear();
}

ClientData& MonitorClients::getClient(int id) {
    // std::lock_guard<std::mutex> lock(mtx);
    return clients.at(id);
}

void MonitorClients::forEachClient(const std::function<void(ClientData&)>& func) {
    // std::lock_guard<std::mutex> lock(mtx);
    for (auto& [id, client] : clients) {
        func(client);
    }
}

void MonitorClients::forClient(int id, const std::function<void(ClientData&)>& func) {
    // std::lock_guard<std::mutex> lock(mtx);
    func(clients.at(id));
}

void MonitorClients::broadcastToAllClients(const Msg& msg) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& [id, client] : clients) {
        client.enqueueMessage(msg);
    }
}

void MonitorClients::killDisconnectedClients() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto it = clients.begin(); it != clients.end();) {
        if (!it->second.isConnected()) {
            it->second.shutdown();
            it = clients.erase(it);
        } else {
            ++it;
        }
    }
}
