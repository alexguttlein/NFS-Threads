#include "client_class.h"

#include <iostream>
#include <ostream>

Client::Client(const char* host, const char* port) :
    clientQueue(Constants::QUEUE_MAXSIZE),
    protocol(clientQueue, host, port) { }

void Client::run() {
    std::string input;

    while (true) {
        std::getline(std::cin, input);

        if (input == "exit") {
            protocol.run();
            break;
        }

        std::istringstream iss(input);
        std::string command;
        iss >> command; // obtiene la primera palabra

        if (command == "nitro") {
            protocol.sendNitro();
        }
        else if (command == "read") {
            int n;
            if (iss >> n) {
                protocol.readMsg(n);
                std::string msg;
                msg = clientQueue.pop();
                std::cout << msg << std::endl;
            } else {
                std::cout << "ERROR: Falta el número en read <n>" << std::endl;
            }
        }
        else {
            std::cout << "Comando desconocido: " << command << std::endl;
        }
    }
}
