#include "client_class.h"

#include <iostream>
#include <ostream>

Client::Client(const char* host, const char* port) :
    protocol(host, port) {
    registerCommands();
}

void Client::run() {
    std::string input;

    while (std::getline(std::cin, input) &&
        input != Constants::INPUT_EXIT) {

        processInput(input);
    }
}

void Client::processInput(std::string input) {
    std::istringstream iss(input);
    std::string command;
    iss >> command;  // obtiene la primera palabra

    dispatcher.dispatch(command, iss);
}

void Client::registerCommands() {
    dispatcher.registerCommand(Constants::INPUT_NITRO, [&](std::istringstream&) {
            protocol.sendNitro();
    });

    dispatcher.registerCommand(Constants::INPUT_READ, [&](std::istringstream& iss) {
        int n;
        if (iss >> n) {
            for (int i = 0; i < n; i++) {
                std::string msg = protocol.readMsg();
                std::cout << msg << std::endl;
            }
        } else {
            std::cout << Constants::ERROR_READN << std::endl;
        }
    });
}
