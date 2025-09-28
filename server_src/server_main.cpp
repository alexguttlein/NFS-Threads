#include <fstream>
#include <iostream>

#include "server_class.h"
#include "../common_src/common_constants.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: La cantidad de parametros no es correcta" << std::endl;
        return Constants::ERROR;
    }

    const char* port = argv[1];
    std::cout << port << std::endl;

    Server server(port);
    server.run();

    return Constants::SUCCESS;
}
