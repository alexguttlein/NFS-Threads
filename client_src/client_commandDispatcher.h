#ifndef COMMANDDISPATCHER_H
#define COMMANDDISPATCHER_H

#include <unordered_map>
#include <functional>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>

class CommandDispatcher {
public:
    void registerCommand(const std::string& name,
                         std::function<void(std::istringstream&)> handler);

    void dispatch(const std::string& name, std::istringstream& iss);

private:
    std::unordered_map<std::string, std::function<void(std::istringstream&)>> commands;
};

#endif  // COMMANDDISPATCHER_H
