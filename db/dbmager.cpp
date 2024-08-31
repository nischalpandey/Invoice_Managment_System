#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "invoice.h"

class Database {
public:
    Database(const std::string& dbPath) : dbPath_(dbPath) {}

    void saveInvoice(Invoice & invoice) {
        std::ofstream file(dbPath_, std::ios::app);
        if (!file) {
            throw std::runtime_error("Unable to open database file for writing");
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
        std::ifstream file(dbPath_);
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
        std::ifstream file(dbPath_);
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
