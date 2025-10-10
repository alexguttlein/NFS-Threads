#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include "../common_src/common_queue.h"
#include "../common_src/common_thread.h"
#include "../common_src/common_message.h"
#include "server_monitorClients.h"
#include <string>
#include <chrono>
#include <thread>

class GameLoop : public Thread {
public:
    GameLoop(Queue<std::string>& queue, MonitorClients& clients);
    void stop() override;
private:
    Queue<std::string>& queue;
    MonitorClients& clients;
    bool running;
    void run() override;
};

#endif  // SERVER_GAMELOOP_H
