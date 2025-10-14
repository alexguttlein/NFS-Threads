#ifndef SERVER_ACCEPTOR_H
#define SERVER_ACCEPTOR_H

#include "../common_src/common_socket.h"
#include "../common_src/common_thread.h"
#include "../common_src/common_queue.h"
#include "server_clientData.h"
#include "server_monitorClients.h"

#include <unordered_map>
#include <arpa/inet.h>
#include <string>
#include <utility>

class Acceptor : public Thread {
public:
    Acceptor(const char* port, MonitorClients& monitor_clients,
        Queue<std::string>& queue);
    void addNewClient(int id, ClientData newClient);
    void run() override;
    void endAccepting();

private:
    Socket socket;
    MonitorClients& monitorClients;
    Queue<std::string>& queue;
    bool keepAccepting;
    void closeSocket();
};

#endif  // SERVER_ACCEPTOR_H
