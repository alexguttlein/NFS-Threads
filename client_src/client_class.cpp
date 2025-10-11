#include "client_class.h"

#include <iostream>
#include <ostream>

Client::Client(const char* host, const char* port) :
    clientQueue(Constants::CLIENT_QUEUE_MAXSIZE),
    protocol(clientQueue, host, port) { }

void Client::run() {
    std::string input;

    while (std::getline(std::cin, input)) {

        if (input == Constants::INPUT_EXIT) {
            protocol.close();
            break;
        }

        processInput(input);
    }
}

void Client::processInput(std::string input) {
    std::istringstream iss(input);
    std::string command;
    iss >> command;  // obtiene la primera palabra

    if (command == Constants::INPUT_NITRO) {
        protocol.sendNitro();
    } else if (command == Constants::INPUT_READ) {
        int n;
        if (iss >> n) {
            protocol.readMsg(n);
            std::string msg;
            for (int i = 0; i < n; i++) {
                msg = clientQueue.pop();
                std::cout << msg << std::endl;
            }
        } else {
            std::cout << Constants::ERROR_READN << std::endl;
        }
    } else {
        std::cout << Constants::ERROR_UNKNOWN_COMMAND << command << std::endl;
    }
}
