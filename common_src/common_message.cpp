#include "common_message.h"

Message::Message(const uint8_t& code) {
    data.code = code;
}

Message::Message() {
    data.code = Constants::DEFAULT_MESSAGE_CODE;
    data.quantity = 0;
    data.type = 0;
}


void Message::addParameters(const int nitrosActivated, const unsigned char type) {
    setType(type);
    setQuantity(nitrosActivated);
}

void Message::setQuantity(const int quantity) {
    uint16_t value = static_cast<uint16_t>(quantity);
    data.quantity = htons(value);
}

void Message::setType(const uint8_t& type) {
    data.type = type;
}

Msg Message::getMessage() {
    return data;
}
