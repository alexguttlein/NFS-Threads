#include "common_messageBuilder.h"

MessageBuilder::MessageBuilder(const uint8_t& code) {
    data.code = code;
}

MessageBuilder::MessageBuilder() {
    data.code = Constants::DEFAULT_MESSAGE_CODE;
    data.quantity = 0;
    data.type = 0;
}


void MessageBuilder::addParameters(const int nitrosActivated, const unsigned char type) {
    setType(type);
    setQuantity(nitrosActivated);
}

void MessageBuilder::setQuantity(const int quantity) {
    uint16_t value = static_cast<uint16_t>(quantity);
    data.quantity = htons(value);
}

void MessageBuilder::setType(const uint8_t& type) {
    data.type = type;
}

Message MessageBuilder::getMessage() {
    return data;
}
