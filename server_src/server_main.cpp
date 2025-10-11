#include <fstream>
#include <iostream>

#include "server_class.h"
#include "../common_src/common_constants.h"

int main(int argc, char* argv[]) {
    if (argc < Constants::EXPECTED_SERVER_ARGC) {
        std::cerr << Constants::ERROR_PARAMETERS_QUANTITY << std::endl;
        return Constants::ERROR;
    }

    const char* port = argv[Constants::PORT_SERVER_ARG_INDEX];

    Server server(port);
    server.run();

    return Constants::SUCCESS;
}
