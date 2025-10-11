#ifndef SERVER_MONITORCLIENTS_H
#define SERVER_MONITORCLIENTS_H

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <unordered_map>
#include <utility>

#include "../common_src/common_message.h"
#include "server_clientData.h"

class MonitorClients {
public:
    MonitorClients();
    void insertClient(int id, ClientData&& client);
    void deleteClient(int id);
    void clear();
    ClientData& getClient(int id);
    void forEachClient(const std::function<void(ClientData&)>& func);
    void forClient(int id, const std::function<void(ClientData&)>& func);
    void broadcastToAllClients(const Message& msg);
    void killDisconnectedClients();

private:
    std::unordered_map<int, ClientData> clients;
    mutable std::mutex mtx;
};

#endif  // SERVER_MONITORCLIENTS_H
