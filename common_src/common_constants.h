#ifndef COMMON_CONSTANTS_H
#define COMMON_CONSTANTS_H

#include <string>

namespace  Constants {

    static constexpr int SUCCESS = 0;
    static constexpr int ERROR = -1;
    static constexpr int NITRO_TIME = 12;
    static const unsigned int QUEUE_MAXSIZE = 20;

    static const std::string INPUT_NITRO = "nitro";
    static const std::string INPUT_READ = "read";
    static const std::string INPUT_EXIT = "exit";

    static const std::string MSG_NITRO_ON = "A car hit the nitro!";
    static const std::string MSG_NITRO_OFF = "A car is out of juice.";

    static constexpr unsigned char CLIENT_ACTIVATE_NITRO = 0x04;
    static constexpr unsigned char SERVER_RESPONSE = 0x10;
    static constexpr unsigned char SERVER_NITRO_ACTIVATE = 0x07;
    static constexpr unsigned char SERVER_NITRO_EXPIRED = 0x08;

    static const std::string ERROR_READN = "ERROR: Falta el número en read <n>";
    static const std::string ERROR_UNKNOWN_COMMAND = "Error: Comando desconocido: ";

};

#endif // COMMON_CONSTANTS_H
