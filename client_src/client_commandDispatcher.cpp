#include "client_commandDispatcher.h"

void CommandDispatcher::registerCommand(const std::string& name,
    std::function<void(std::istringstream&)> handler) {

    commands[name] = std::move(handler);
}

void CommandDispatcher::dispatch(const std::string& name, std::istringstream& iss) {
    auto it = commands.find(name);
    if (it != commands.end()) {
        it->second(iss);
    } else {
        std::cout << "Comando desconocido: " << name << std::endl;
    }
}
