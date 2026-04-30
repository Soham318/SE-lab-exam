#include "BookingSystem.h"
#include "Sender.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <vector>

BookingSystem::BookingSystem() {}

Shipment* BookingSystem::createShipmentRecord(double weight, const std::string& dimensions, const std::string& serviceType) {
    Shipment* shipment = new Shipment();
    shipment->storePackageDetails(weight, dimensions);
    shipment->generateTrackingID();
    
    std::string label = "LBL-" + shipment->getTrackingID() + "-" + serviceType;
    shipment->storeServiceTypeAndLabel(serviceType, label);
    
    return shipment;
}

void BookingSystem::printLabelAndConfirm(Sender* sender, Shipment* shipment) {
    shipment->printShipmentDetails();
}

bool parseDate(const std::string& dateStr, int& day, int& month, int& year) {
    if (dateStr == "NULL" || dateStr.empty()) return false;
    
    std::stringstream ss(dateStr);
    std::string item;
    std::vector<std::string> parts;
    while (std::getline(ss, item, '-')) {
        parts.push_back(item);
    }
    
    if (parts.size() != 3) return false;
    
    for (const std::string& part : parts) {
        if (part.empty()) return false;
        for (char c : part) {
            if (!isdigit(c)) return false;
        }
    }
    
    try {
        day = std::stoi(parts[0]);
        month = std::stoi(parts[1]);
        year = std::stoi(parts[2]);
        
        if (month <= 0 || month > 12) return false;
        if (day <= 0 || day > 31) return false;
        if (year <= 0) return false;
        return true;
    } catch (...) {
        return false;
    }
}

std::string BookingSystem::validateDeliveryDate(const std::string& bookingDate, const std::string& deliveryDate) {
    int bDay, bMonth, bYear, dDay, dMonth, dYear;
    
    if (!parseDate(bookingDate, bDay, bMonth, bYear) || !parseDate(deliveryDate, dDay, dMonth, dYear)) {
        return "Error: Invalid input (null/negative/non-numeric values not allowed)";
    }
    
    bool isValid = false;
    if (dYear > bYear) {
        isValid = true;
    } else if (dYear == bYear) {
        if (dMonth > bMonth) {
            isValid = true;
        } else if (dMonth == bMonth && dDay > bDay) {
            isValid = true;
        }
    }
    
    if (isValid) {
        return "Accepted";
    }
    
    return "Error: Delivery date must be after booking date";
}

std::string BookingSystem::validatePackageCount(const std::string& countStr) {
    if (countStr == "NULL" || countStr.empty()) return "Error: Invalid input (null/negative/non-numeric values not allowed)";
    
    for (char c : countStr) {
        if (c == '-' && &c == &countStr[0]) continue; 
        if (!isdigit(c)) return "Error: Invalid input (null/negative/non-numeric values not allowed)"; 
    }
    
    try {
        int count = std::stoi(countStr);
        if (count <= 0) return "Error: Invalid input (null/negative/non-numeric values not allowed)";
        if (count > 5) return "Error: Package limit exceeded (Max = 5)";
        return "Accepted";
    } catch (...) {
        return "Error: Invalid input (null/negative/non-numeric values not allowed)";
    }
}
