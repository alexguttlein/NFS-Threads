#ifndef SERVER_ACCEPTOR_H
#define SERVER_ACCEPTOR_H

#include "../common_src/common_clientData.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_thread.h"

#include <unordered_map>
#include <arpa/inet.h>

class Acceptor : public Thread {
public:
    Acceptor(const char* port, std::unordered_map<int, ClientData>& clients);
    void run() override;
    void endAccepting();
private:
    Socket socket;
    std::unordered_map<int, ClientData>& clients;
    bool keepAccepting;
    void close();
};

#endif  // SERVER_ACCEPTOR_H
