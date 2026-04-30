#ifndef SENDER_H
#define SENDER_H

#include <string>

class BookingSystem;
class Shipment;

class Sender {
private:
    std::string name;
    std::string senderAddress;
    std::string receiverAddress;
    std::string selectedServiceType;

public:
    Sender(const std::string& senderName);

    void enterDetails(const std::string& sAddress, const std::string& rAddress);
    void selectServiceType(const std::string& serviceType);

    std::string getName() const;
};

#endif // SENDER_H
