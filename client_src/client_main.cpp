#include <fstream>
#include <iostream>
#include <string>

#include "../common_src/common_constants.h"
#include "client_class.h"

int main(int argc, char* argv[]) {
    if (argc < Constants::EXPECTED_CLIENT_ARGC) {
        std::cerr << Constants::ERROR_PARAMETERS_QUANTITY << std::endl;
        return Constants::ERROR;
    }

    const char* host = argv[Constants::HOST_CLIENT_ARG_INDEX];
    const char* port = argv[Constants::PORT_CLIENT_ARG_INDEX];

    try {
        Client client(host, port);
        client.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return Constants::SUCCESS;
}
