#include <string>

class Item {
public:
    Item(const std::string& name, double price, int quantity)
        : name_(name), price_(price), quantity_(quantity) {}

    double getTotalPrice() const { return price_ * quantity_; }
    std::string getName() const { return name_; }
    double getPrice() const { return price_; }
    int getQuantity() const { return quantity_; }

private:
    std::string name_;
    double price_;
    int quantity_;
};
