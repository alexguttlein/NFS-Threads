#include "server_senderThread.h"

SenderThread::SenderThread(Socket* socket, Queue<uint8_t>* clientQueue) :
    socket(socket), keepRunning(true), clientQueue(clientQueue) {}

/*void SenderThread::run() {
    std::cout << "DEBUG: Sender Thread Started" << std::endl;
    // while (keepRunning) {
        uint8_t msg(0);
        while (clientQueue->try_pop(msg) && keepRunning) {
            // std::cout << "DEBUG" << std::endl;
            try {
                std::cout << "DEBUG: SenderThread::run -> antes de sendall" << std::endl;
                if (socket->is_stream_send_closed() || socket->is_stream_recv_closed()) {
                    keepRunning = false;
                    break;
                }
                socket->sendall(&msg, sizeof(msg));
                std::cout << "DEBUG: SenderThread::run -> despues de sendall" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "SenderThread error: " << e.what() << std::endl;
                keepRunning = false;
            }
        }
    // }
}*/

void SenderThread::run() {
    // std::cout << "DEBUG: SenderThread iniciado" << std::endl;
    try {
        while (keepRunning) {
            uint8_t msg = clientQueue->pop();

            // se verifica si el socket está cerrado antes de enviar
            if (socket->is_stream_send_closed() || socket->is_stream_recv_closed()) {
                // std::cout << "DEBUG: socket cerrado, fin del SenderThread" << std::endl;
                keepRunning = false;
                break;
            }

            // std::cout << "DEBUG: SenderThread -> enviando mensaje (" << (int)msg << ")" << std::endl;
            socket->sendall(&msg, sizeof(msg));
            // std::cout << "DEBUG: SenderThread -> mensaje enviado" << std::endl;
        }
    } catch (const ClosedQueue& e) {
        // std::cout << "DEBUG: Cola cerrada, SenderThread finaliza." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "SenderThread error: " << e.what() << std::endl;
    }
    // std::cout << "DEBUG: SenderThread finalizado." << std::endl;
}
