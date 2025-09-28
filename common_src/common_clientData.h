#ifndef CLIENTDATA_H
#define CLIENTDATA_H
#include "common_socket.h"
// #include "../server_src/server_senderThread.h"
// #include "../server_src/server_receiverThread.h"

#include <arpa/inet.h>

struct ClientData {
    int id;
    Socket socket;
    // SenderThread senderThread;
    // ReceiverThread receiverThread;

    void shutdown() {
        socket.shutdown(SHUT_RDWR);
        socket.close();
        /*if (senderThread) {
            senderThread->end();
            senderThread->join();
            delete senderThread;
            senderThread = nullptr;
        }
        if (receiverThread) {
            receiverThread->end();
            receiverThread->join();
            delete receiverThread;
            receiverThread = nullptr;
        }*/
    }

};

#endif  // CLIENTDATA_H
