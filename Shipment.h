#ifndef SHIPMENT_H
#define SHIPMENT_H

#include <string>

class BookingSystem; // Forward declaration

class Shipment {
private:
    double weight;
    std::string dimensions;
    std::string trackingID;
    std::string serviceType;
    std::string label;

public:
    Shipment();

    void storePackageDetails(double w, const std::string& dims);
    void generateTrackingID();
    void storeServiceTypeAndLabel(const std::string& type, const std::string& lbl);

    std::string getTrackingID() const;
    std::string getServiceType() const;
    void printShipmentDetails() const;

    std::string updateShipmentStatus(const std::string& currentStatus, const std::string& newStatus, int daysInTransit, bool isPaymentCleared);
};

#endif // SHIPMENT_H
