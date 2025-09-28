#ifndef COMMON_CONSTANTS_H
#define COMMON_CONSTANTS_H

#include <string_view>
#include <string>


class Constants {
public:
    static constexpr int SUCCESS = 0;
    static constexpr int ERROR = -1;

    const char* MSG_NITRO_ON = "A car hit the nitro!";
    const char* MSG_NITRO_OFF = "A car is out of juice.";

    static constexpr unsigned char CLIENT_ACTIVATE_NITRO = 0x04;
    static constexpr unsigned char SERVER_RESPONSE = 0x10;
    static constexpr unsigned char SERVER_NITRO_ACTIVATE = 0x07;
    static constexpr unsigned char SERVER_NITRO_EXPIRED = 0x08;

};

#endif // COMMON_CONSTANTS_H
