#ifndef BOOKINGSYSTEM_H
#define BOOKINGSYSTEM_H

#include <string>
#include "Shipment.h"

class Sender; // Forward declaration

class BookingSystem {
public:
    BookingSystem();

    std::string validateDeliveryDate(const std::string& bookingDate, const std::string& deliveryDate);
    std::string validatePackageCount(const std::string& countStr);

    Shipment* createShipmentRecord(double weight, const std::string& dimensions, const std::string& serviceType);
    void printLabelAndConfirm(Sender* sender, Shipment* shipment);
};

#endif // BOOKINGSYSTEM_H
