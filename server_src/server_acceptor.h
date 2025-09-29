#ifndef SERVER_ACCEPTOR_H
#define SERVER_ACCEPTOR_H

#include <unordered_map>

#include <arpa/inet.h>

#include "../common_src/common_clientData.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_thread.h"

#include "MonitorClients.h"

class Acceptor : public Thread {
public:
    Acceptor(const char* port, MonitorClients& monitorClients);
    void run() override;
    void endAccepting();
private:
    Socket socket;
    // std::unordered_map<int, ClientData>& clients;
    MonitorClients& monitorClients;
    bool keepAccepting;
    void close();
};

#endif  // SERVER_ACCEPTOR_H
