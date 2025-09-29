#include <fstream>
#include <iostream>
#include <string>

#include "../common_src/common_constants.h"
#include "client_class.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Error: La cantidad de parametros no es correcta" << std::endl;
        return Constants::ERROR;
    }

    const char* host = argv[1];
    const char* port = argv[2];

    try {
        Client client(host, port);
        client.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return Constants::SUCCESS;
}
