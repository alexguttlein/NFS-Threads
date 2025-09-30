#ifndef SERVER_MONITORCLIENTS_H
#define SERVER_MONITORCLIENTS_H

#include "server_clientData.h"

#include <condition_variable>
#include <mutex>
#include <unordered_map>
#include <iostream>
#include <functional>

class MonitorClients {
public:
    MonitorClients();
    void insertClient(int id, ClientData&& client);
    void deleteClient(int id);
    void clear();
    ClientData& getClient(int id);
    void forEachClient(const std::function<void(ClientData&)>& func);
private:
    std::unordered_map<int, ClientData> clients;
    mutable std::mutex mtx;
};

#endif  // SERVER_MONITORCLIENTS_H
