#include <string>
#include <vector> // For vector operations (e.g., std::vector)
#include <fstream> // For file I/O operations (e.g., std::ifstream, std::ofstream)
#include <sstream> // For string stream operations (e.g., std::istringstream)
#include <stdexcept> // For std::runtime_error
#include "../invoice.cpp"
#include "../models/collegeinfo.cpp"
#include "../models/item.cpp"
#include <iostream> 
#include <filesystem> // For filesystem operations


class Database {
public:
    Database(const std::string& dbPath) : dbPath_(dbPath) {
        // Extract the directory path from the dbPath
        std::filesystem::path dirPath = std::filesystem::path(dbPath_).parent_path();

        // Check if the directory exists
        if (!std::filesystem::exists(dirPath)) {
            // Create the directory if it does not exist
            std::filesystem::create_directories(dirPath);
        }
    }
    
    bool checkCollegeinfo() {
        std::ifstream file(dbPath_ , std::ios::out|std::ios::binary);
        if (!file) {
            return false;
        }
        return true;
    }
    



    void saveCollegeinfo(const CollegeInfo & collegeinfo) {
        std::ofstream file(dbPath_, std::ios::app | std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open or create database file for writing");
        }
        file << collegeinfo.getName() << "|"
             << collegeinfo.getAddress() << "|"
             << collegeinfo.getPhone() << "|"
             << collegeinfo.getEmail() << "|"
             << collegeinfo.getWebsite() << "|"
             << collegeinfo.getPan() << "\n";
    }

    void saveInvoice(Invoice & invoice) {

    // print dbpath
    std::cout << dbPath_ << std::endl;

    // All modes are supported ,so error handling is not required
        // Try to open the file in append mode; if it doesn't exist, create it
    std::ofstream file(dbPath_, std::ios::app | std::ios::binary);
    
    // Check if the file was successfully opened
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open or create database file for writing");
    }
        file << invoice.getInvoiceNumber() << "|"
             << invoice.getStudentName() << "|"
             << invoice.getStudentID() << "|"
             << invoice.getCurrentDate() << "|"
             << invoice.getTotalAmount() << "\n";

        for (const auto& item : invoice.getItems()) {
            file << "ITEM|" << item.getName() << "|" << item.getPrice() << "|" << item.getQuantity() << "\n";
        }

        file << "END\n";
    }

    Invoice getInvoice(const std::string& invoiceNumber) {
        std::ifstream file(dbPath_ , std::ios::out|std::ios::binary);
        if (!file) {
            throw std::runtime_error("Unable to open database file for reading");
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string currentInvoiceNumber;
            std::getline(iss, currentInvoiceNumber, '|');

            if (currentInvoiceNumber == invoiceNumber) {
                std::string studentName, studentID, date;
                double totalAmount;
                std::getline(iss, studentName, '|');
                std::getline(iss, studentID, '|');
                std::getline(iss, date, '|');
                iss >> totalAmount;

                Invoice invoice(studentName, studentID);
                invoice.setInvoiceNumber(invoiceNumber);
                invoice.setCurrentDate(date);

                while (std::getline(file, line) && line != "END") {
                    std::istringstream itemIss(line);
                    std::string itemType;
                    std::getline(itemIss, itemType, '|');
                    if (itemType == "ITEM") {
                        std::string itemName;
                        double price;
                        int quantity;
                        std::getline(itemIss, itemName, '|');
                        itemIss >> price;
                        itemIss.ignore();
                        itemIss >> quantity;
                        invoice.addItem(Item(itemName, price, quantity));
                    }
                }

                return invoice;
            }

            // Skip to the end of the current invoice
            while (std::getline(file, line) && line != "END") {}
        }

        return Invoice("", ""); // Return empty invoice if not found
    }

    std::vector<std::string> getAllInvoiceNumbers() {
        std::vector<std::string> invoiceNumbers;
        std::ifstream file(dbPath_ , std::ios::app|std::ios::out|std::ios::in|std::ios::binary);
        if (!file) {
            throw std::runtime_error("Unable to open database file for reading");
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string invoiceNumber;
            std::getline(iss, invoiceNumber, '|');
            invoiceNumbers.push_back(invoiceNumber);

            // Skip to the end of the current invoice
            while (std::getline(file, line) && line != "END") {}
        }

        return invoiceNumbers;
    }

private:
    std::string dbPath_;
};
