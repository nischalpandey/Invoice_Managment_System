#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Forward declarations
class Item;
class Invoice;
class InvoiceManager;

class Item {
public:
    Item(const std::string& name, double price, int quantity)
        : name_(name), price_(price), quantity_(quantity) {}

    double getTotalPrice() const { return price_ * quantity_; }

    // Getters
    std::string getName() const { return name_; }
    double getPrice() const { return price_; }
    int getQuantity() const { return quantity_; }

private:
    std::string name_;
    double price_;
    int quantity_;
};

class Invoice {
public:
    Invoice(const std::string& customerName, const std::string& date)
        : customerName_(customerName), date_(date) {}

    void addItem(const Item& item) {
        items_.push_back(item);
    }

    double getTotalAmount() const {
        double total = 0;
        for (const auto& item : items_) {
            total += item.getTotalPrice();
        }
        return total;
    }

    // Getters
    std::string getCustomerName() const { return customerName_; }
    std::string getDate() const { return date_; }
    const std::vector<Item>& getItems() const { return items_; }

private:
    std::string customerName_;
    std::string date_;
    std::vector<Item> items_;
};

class InvoiceManager {
public:
    void createInvoice(const std::string& customerName, const std::string& date) {
        invoices_.push_back(std::make_unique<Invoice>(customerName, date));
    }

    void addItemToInvoice(int invoiceIndex, const Item& item) {
        if (invoiceIndex >= 0 && invoiceIndex < invoices_.size()) {
            invoices_[invoiceIndex]->addItem(item);
        }
    }

    void displayInvoice(int invoiceIndex) const {
        if (invoiceIndex >= 0 && invoiceIndex < invoices_.size()) {
            const auto& invoice = invoices_[invoiceIndex];
            std::cout << "Invoice for: " << invoice->getCustomerName() << std::endl;
            std::cout << "Date: " << invoice->getDate() << std::endl;
            std::cout << "Items:" << std::endl;
            for (const auto& item : invoice->getItems()) {
                std::cout << item.getName() << " - $" << item.getPrice() 
                          << " x " << item.getQuantity() << " = $" << item.getTotalPrice() << std::endl;
            }
            std::cout << "Total Amount: $" << invoice->getTotalAmount() << std::endl;
        }
    }

private:
    std::vector<std::unique_ptr<Invoice>> invoices_;
};

int main() {
    InvoiceManager manager;

    // Create an invoice
    manager.createInvoice("John Doe", "2024-08-30");

    // Add items to the invoice
    manager.addItemToInvoice(0, Item("Pencil", 0.5, 10));
    manager.addItemToInvoice(0, Item("Notebook", 2.0, 5));
    manager.addItemToInvoice(0, Item("Eraser", 0.75, 3));

    // Display the invoice
    manager.displayInvoice(0);
    int a;
    std::cin >> a;
    

    return 0;
}