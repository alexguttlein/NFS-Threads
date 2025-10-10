#ifndef COMMON_MESSAGE_H
#define COMMON_MESSAGE_H

#include "common_constants.h"
#include <cstdint>
#include <arpa/inet.h>

struct Msg {
    uint8_t code;
    uint16_t quantity;
    uint8_t type;
};

class Message {
public:
    explicit Message(const uint8_t& code);
    Message();
    void addParameters(const int nitrosActivated,
        const unsigned char type);
    Msg getMessage();

private:
    Msg data{};
    void setQuantity(const int quantity);
    void setType(const uint8_t& type);
};

#endif  // COMMON_MESSAGE_H
