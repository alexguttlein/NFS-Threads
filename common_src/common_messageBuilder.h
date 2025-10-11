#ifndef COMMON_MESSAGE_H
#define COMMON_MESSAGE_H

#include <cstdint>

#include <arpa/inet.h>

#include "common_constants.h"
// #include "common_message.h"

#pragma pack(push, 1)  // para evitar padding
struct Message {
    uint8_t code;
    uint16_t quantity;
    uint8_t type;
};
#pragma pack(pop)

class MessageBuilder {
public:
    explicit MessageBuilder(const uint8_t& code);
    MessageBuilder();
    void addParameters(const int nitrosActivated,
        const unsigned char type);
    Message getMessage();

private:
    Message data{};
    void setQuantity(const int quantity);
    void setType(const uint8_t& type);
};

#endif  // COMMON_MESSAGE_H
