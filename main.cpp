#include <iostream>
#include <string>
#include "Sender.h"
#include "BookingSystem.h"
#include "Shipment.h"

int main() {
    BookingSystem bookingSystem;
    
    while (true) {
        std::string senderName, receiverName, address, serviceType, bookingDate, deliveryDate, countStr, weightStr;
        
        std::cout << "Enter Sender Name: ";
        std::getline(std::cin, senderName);
        
        std::cout << "Enter Receiver Name: ";
        std::getline(std::cin, receiverName);
        
        std::cout << "Enter Address: ";
        std::getline(std::cin, address);
        
        std::cout << "Enter Package Weight: ";
        std::getline(std::cin, weightStr);
        
        std::cout << "Enter Service Type: ";
        std::getline(std::cin, serviceType);
        
        std::cout << "Enter Booking Date: ";
        std::getline(std::cin, bookingDate);
        
        std::cout << "Enter Delivery Date: ";
        std::getline(std::cin, deliveryDate);
        
        std::cout << "Enter Package Count: ";
        std::getline(std::cin, countStr);
        
        std::cout << "\n";
        
        // Weight Validation (covers invalid input for weight)
        try {
            double w = std::stod(weightStr);
            if (w <= 0) throw std::invalid_argument("negative");
        } catch (...) {
            std::cout << "Error: Invalid input (null/negative/non-numeric values not allowed)\n";
            std::cout << "\nRe-enter shipment details:\n\n";
            continue;
        }

        // Date Validation
        std::string dateResult = bookingSystem.validateDeliveryDate(bookingDate, deliveryDate);
        if (dateResult != "Accepted") {
            std::cout << dateResult << std::endl;
            if (dateResult == "Error: Delivery date must be after booking date") {
                std::cout << "Please re-enter details\n\nRe-enter shipment details:\n\n";
            } else {
                std::cout << "\nRe-enter shipment details:\n\n";
            }
            continue;
        }
        
        // Count Validation
        std::string countResult = bookingSystem.validatePackageCount(countStr);
        if (countResult != "Accepted") {
            std::cout << countResult << std::endl;
            std::cout << "\nRe-enter shipment details:\n\n";
            continue;
        }
        
        // Success path
        Sender mySender(senderName);
        mySender.enterDetails(address, address); // Just to satisfy class interaction
        mySender.selectServiceType(serviceType);
        
        Shipment* shipment = bookingSystem.createShipmentRecord(std::stod(weightStr), "Standard", serviceType);
        bookingSystem.printLabelAndConfirm(&mySender, shipment);
        
        delete shipment;
        break; // End after successful booking
    }
    
    return 0;
}
