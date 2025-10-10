#ifndef SERVER_CLIENTDATA_H
#define SERVER_CLIENTDATA_H

#include "../common_src/common_socket.h"
#include "../common_src/common_queue.h"
#include "../common_src/common_constants.h"
#include "../common_src/common_message.h"
#include "server_senderThread.h"
#include "server_receiverThread.h"

#include <arpa/inet.h>
#include <memory>
#include <string>
#include <utility>

class ClientData {
public:
    ClientData(int id, Socket&& socket, Queue<std::string>& queue);
    void startThreads();
    void shutdown();
    void activateNitro();
    bool nitroEnded();

    int getId() const { return id; }
    int getNitroTime() const { return nitroTime; }
    void enqueueMessage(const Msg& msg);
    bool isConnected() const;

private:
    int id;
    Socket socket;
    Queue<std::string>& serverQueue;
    std::unique_ptr<SenderThread> senderThread;
    std::unique_ptr<ReceiverThread> receiverThread;
    int nitroTime;
    std::unique_ptr<Queue<Msg>> clientQueue;
};

#endif  // SERVER_CLIENTDATA_H
