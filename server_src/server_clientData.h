#ifndef SERVER_CLIENTDATA_H
#define SERVER_CLIENTDATA_H

#include <memory>
#include <string>
#include <utility>

#include <arpa/inet.h>

#include "../common_src/common_constants.h"
#include "../common_src/common_message.h"
#include "../common_src/common_queue.h"
#include "../common_src/common_socket.h"

#include "server_receiverThread.h"
#include "server_senderThread.h"
#include "server_protocol.h"

class ClientData {
public:
    ClientData(int id, Socket&& socket, Queue<std::string>& queue);
    void startThreads();
    void shutdown();
    void activateNitro();
    bool nitroEnded();

    int getId() const { return id; }
    int getNitroTime() const { return nitroTime; }
    void enqueueMessage(const Message& msg);
    bool isConnected() const;

private:
    int id;
    ServerProtocol serverProtocol;
    Queue<std::string>& serverQueue;
    std::unique_ptr<SenderThread> senderThread;
    std::unique_ptr<ReceiverThread> receiverThread;
    int nitroTime;
    std::unique_ptr<Queue<Message>> clientQueue;
};

#endif  // SERVER_CLIENTDATA_H
