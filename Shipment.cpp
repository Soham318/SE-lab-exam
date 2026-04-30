#include "Shipment.h"
#include <cstdlib>
#include <iostream>

Shipment::Shipment() : weight(0.0), dimensions(""), trackingID(""), serviceType(""), label("") {}

void Shipment::storePackageDetails(double w, const std::string& dims) {
    weight = w;
    dimensions = dims;
}

void Shipment::generateTrackingID() {
    trackingID = "TRK12345";
}

void Shipment::storeServiceTypeAndLabel(const std::string& type, const std::string& lbl) {
    serviceType = type;
    label = lbl;
}

std::string Shipment::getTrackingID() const {
    return trackingID;
}

std::string Shipment::getServiceType() const {
    return serviceType;
}

void Shipment::printShipmentDetails() const {
    std::cout << "Booking Successful!" << std::endl;
    std::cout << "Tracking ID: " << trackingID << std::endl;
    std::cout << "Service Type: " << serviceType << std::endl;
    std::cout << "Shipment Label Generated" << std::endl;
}

std::string Shipment::updateShipmentStatus(const std::string& currentStatus, const std::string& newStatus, int daysInTransit, bool isPaymentCleared) {
    if (!isPaymentCleared) {
        return "Error: Payment not cleared"; // Line 41
    }
    
    if (currentStatus == newStatus) {
        return "Error: Status already " + currentStatus; // Line 45
    }

    if (currentStatus == "Pending") {
        if (newStatus == "Dispatched") {
            return "Success: Dispatched"; // Line 50
        } else if (newStatus == "Cancelled") {
            return "Success: Cancelled"; // Line 52
        } else {
            return "Error: Invalid transition from Pending"; // Line 54
        }
    } else if (currentStatus == "Dispatched") {
        if (newStatus == "In Transit" && daysInTransit > 0) {
            return "Success: In Transit"; // Line 59
        } else if (newStatus == "Delivered") {
            return "Error: Cannot skip In Transit"; // Line 61
        } else {
            return "Error: Invalid transition from Dispatched"; // Line 63
        }
    } else if (currentStatus == "In Transit") {
        if (newStatus == "Delivered" && daysInTransit >= 2) {
            return "Success: Delivered"; // Line 68
        } else if (newStatus == "Lost" && daysInTransit > 7) {
            return "Status Updated to Lost"; // Line 70
        } else {
            return "Error: Invalid transition from In Transit or days too low"; // Line 72
        }
    } else if (currentStatus == "Delivered" || currentStatus == "Cancelled") {
        return "Error: Terminal state"; // Line 75
    }
    
    return "Error: Unknown Status"; // Line 78
}
