#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include "../common_src/common_queue.h"
#include "../common_src/common_thread.h"
#include "../common_src/common_messageBuilder.h"
#include "server_monitorClients.h"
#include <string>
#include <chrono>
#include <thread>

class GameLoop : public Thread {
public:
    GameLoop(Queue<std::string>& queue, MonitorClients& clients);
    void checkNitroExpirationAndBroadcast(int& nitrosActivated);
    void unqueueAndBroadcastMsg(int& nitrosActivated);
    void stop() override;
    ~GameLoop();
private:
    Queue<std::string>& queue;
    MonitorClients& clients;
    bool running;
    void run() override;
};

#endif  // SERVER_GAMELOOP_H
