#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "BookingSystem.h"

struct DateTestCase {
    std::string id;
    std::string desc;
    std::string bDate;
    std::string dDate;
    std::string expected;
};

struct CountTestCase {
    std::string id;
    std::string desc;
    std::string countStr;
    std::string expected;
};

int main() {
    BookingSystem system;
    
    std::vector<DateTestCase> dateTests = {
        {"TC01", "Valid delivery date", "10-05-2026", "12-05-2026", "Accepted"},
        {"TC02", "Delivery = booking date", "10-05-2026", "10-05-2026", "Error: Delivery date must be after booking date"},
        {"TC03", "Delivery before booking", "10-05-2026", "09-05-2026", "Error: Delivery date must be after booking date"},
        {"TC04", "Just after booking", "10-05-2026", "11-05-2026", "Accepted"},
        {"TC05", "Far future date", "10-05-2026", "30-05-2026", "Accepted"},
        {"TC06", "Null delivery date", "10-05-2026", "NULL", "Error: Invalid input (null/negative/non-numeric values not allowed)"},
        {"TC07", "Invalid date format", "10-05-2026", "abc", "Error: Invalid input (null/negative/non-numeric values not allowed)"}
    };
    
    std::vector<CountTestCase> countTests = {
        {"TC08", "Package within limit", "3", "Accepted"},
        {"TC09", "Package at max limit", "5", "Accepted"},
        {"TC10", "Package exceeds limit", "6", "Error: Package limit exceeded (Max = 5)"},
        {"TC11", "Just below max", "4", "Accepted"},
        {"TC12", "Zero package", "0", "Error: Invalid input (null/negative/non-numeric values not allowed)"},
        {"TC13", "Negative package", "-1", "Error: Invalid input (null/negative/non-numeric values not allowed)"},
        {"TC14", "Null package count", "NULL", "Error: Invalid input (null/negative/non-numeric values not allowed)"},
        {"TC15", "Non-numeric package", "five", "Error: Invalid input (null/negative/non-numeric values not allowed)"}
    };
    
    int passedCount = 0;
    int totalTests = dateTests.size() + countTests.size();

    std::cout << "========================================================================================\n";
    std::cout << std::left << std::setw(6) << "ID" 
              << std::setw(25) << "Scenario" 
              << std::setw(48) << "Expected Output" 
              << "Result\n";
    std::cout << "========================================================================================\n";
    
    for (const auto& tc : dateTests) {
        std::string actual = system.validateDeliveryDate(tc.bDate, tc.dDate);
        std::string result = (actual == tc.expected) ? "PASS" : "FAIL";
        if (result == "PASS") passedCount++;
        
        std::cout << std::left << std::setw(6) << tc.id 
                  << std::setw(25) << tc.desc 
                  << std::setw(48) << tc.expected.substr(0, 46) 
                  << result << "\n";
    }
    
    for (const auto& tc : countTests) {
        std::string actual = system.validatePackageCount(tc.countStr);
        std::string result = (actual == tc.expected) ? "PASS" : "FAIL";
        if (result == "PASS") passedCount++;
        
        std::cout << std::left << std::setw(6) << tc.id 
                  << std::setw(25) << tc.desc 
                  << std::setw(48) << tc.expected.substr(0, 46) 
                  << result << "\n";
    }
    
    std::cout << "========================================================================================\n";
    std::cout << "Total Black Box Tests Passed: " << passedCount << " / " << totalTests << "\n";
    return 0;
}
