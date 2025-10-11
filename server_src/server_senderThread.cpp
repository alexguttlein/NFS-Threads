#include "server_senderThread.h"

SenderThread::SenderThread(ServerProtocol* serverProtocol, Queue<Message>* clientQueue) :
    serverProtocol(serverProtocol), keepRunning(true), clientQueue(clientQueue) {}

void SenderThread::run() {
    try {
        while (keepRunning) {
            Message msg = clientQueue->pop();

            // se verifica si el socket está cerrado antes de enviar
            if (serverProtocol->isConnectionClosed()) {
                keepRunning = false;
                break;
            }

            serverProtocol->sendMessage(msg);
            // socket->sendall(&msg, sizeof(msg));
        }
    } catch (const ClosedQueue& e) {
        // std::cerr << "SenderThread ClosedQueue: " << e.what() << std::endl;
        keepRunning = false;
    } catch (const std::exception& e) {
        std::cerr << "SenderThread error: " << e.what() << std::endl;
    }
}
