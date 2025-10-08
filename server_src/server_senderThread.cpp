#include "server_senderThread.h"

SenderThread::SenderThread(Socket* socket, Queue<uint8_t>* clientQueue) :
    socket(socket), keepRunning(true), clientQueue(clientQueue) {}

void SenderThread::run() {
    try {
        while (keepRunning) {
            uint8_t msg = clientQueue->pop();

            // se verifica si el socket está cerrado antes de enviar
            if (socket->is_stream_send_closed() || socket->is_stream_recv_closed()) {
                keepRunning = false;
                break;
            }
            socket->sendall(&msg, sizeof(msg));
        }
    } catch (const ClosedQueue& e) {
        std::cerr << "SenderThread ClosedQueue: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "SenderThread error: " << e.what() << std::endl;
    }
}
