#ifndef COMMON_MESSAGE_H
#define COMMON_MESSAGE_H

#include <cstdint>

#pragma pack(push, 1)  // para evitar padding
struct Message {
    uint8_t code;
    uint16_t quantity;
    uint8_t type;
};
#pragma pack(pop)

#endif  // COMMON_MESSAGE_H
