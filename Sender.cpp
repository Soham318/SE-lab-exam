#include "Sender.h"

Sender::Sender(const std::string& senderName) : name(senderName), senderAddress(""), receiverAddress(""), selectedServiceType("") {}

void Sender::enterDetails(const std::string& sAddress, const std::string& rAddress) {
    senderAddress = sAddress;
    receiverAddress = rAddress;
}

void Sender::selectServiceType(const std::string& serviceType) {
    selectedServiceType = serviceType;
}

std::string Sender::getName() const {
    return name;
}
