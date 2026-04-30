#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Shipment.h"

struct TestCase {
    std::string id;
    std::string currentStatus;
    std::string newStatus;
    int daysInTransit;
    bool isPaymentCleared;
    std::string expectedOutput;
};

int main() {
    Shipment shipment;
    
    std::vector<TestCase> testCases = {
        {"TC01", "Pending", "Dispatched", 0, false, "Error: Payment not cleared"},
        {"TC02", "Pending", "Pending", 0, true, "Error: Status already Pending"},
        {"TC03", "Pending", "Dispatched", 0, true, "Success: Dispatched"},
        {"TC04", "Pending", "Cancelled", 0, true, "Success: Cancelled"},
        {"TC05", "Pending", "Delivered", 0, true, "Error: Invalid transition from Pending"},
        {"TC06", "Dispatched", "In Transit", 1, true, "Success: In Transit"},
        {"TC07", "Dispatched", "In Transit", 0, true, "Error: Invalid transition from Dispatched"},
        {"TC08", "Dispatched", "Delivered", 5, true, "Error: Cannot skip In Transit"},
        {"TC09", "Dispatched", "Cancelled", 0, true, "Error: Invalid transition from Dispatched"},
        {"TC10", "In Transit", "Delivered", 2, true, "Success: Delivered"},
        {"TC11", "In Transit", "Delivered", 1, true, "Error: Invalid transition from In Transit or days too low"},
        {"TC12", "In Transit", "Lost", 8, true, "Status Updated to Lost"},
        {"TC13", "In Transit", "Lost", 7, true, "Error: Invalid transition from In Transit or days too low"},
        {"TC14", "Delivered", "Return", 0, true, "Error: Terminal state"},
        {"TC15", "Unknown", "Pending", 0, true, "Error: Unknown Status"}
    };

    std::cout << "========================================================================\n";
    std::cout << std::left << std::setw(6) << "ID" 
              << std::setw(30) << "Expected" 
              << std::setw(30) << "Actual" 
              << "Result\n";
    std::cout << "========================================================================\n";

    int passedCount = 0;
    
    for (const auto& tc : testCases) {
        std::string actualOutput = shipment.updateShipmentStatus(
            tc.currentStatus, tc.newStatus, tc.daysInTransit, tc.isPaymentCleared
        );
        
        std::string result = (actualOutput == tc.expectedOutput) ? "PASS" : "FAIL";
        if (result == "PASS") passedCount++;
        
        std::cout << std::left << std::setw(6) << tc.id 
                  << std::setw(30) << tc.expectedOutput.substr(0, 28) 
                  << std::setw(30) << actualOutput.substr(0, 28) 
                  << result << "\n";
    }
    
    std::cout << "========================================================================\n";
    std::cout << "Total Passed: " << passedCount << " / " << testCases.size() << "\n";

    return 0;
}
