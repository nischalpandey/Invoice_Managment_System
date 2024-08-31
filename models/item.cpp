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
//
class Student {
// name, roll, address, phone, email, course, semester, year

public:
    Student(const std::string& name, const std::string& roll, const std::string& address, const std::string& phone, const std::string& email, const std::string& course, const std::string& semester, const std::string& year)
        : name_(name), roll_(roll), address_(address), phone_(phone), email_(email), course_(course), semester_(semester), year_(year) {}

    std::string getName() const { return name_; }
    std::string getRoll() const { return roll_; }
    std::string getAddress() const { return address_; }
    std::string getPhone() const { return phone_; }
    std::string getEmail() const { return email_; }
    std::string getCourse() const { return course_; }
    std::string getSemester() const { return semester_; }
    std::string getYear() const { return year_; }

private:
    std::string name_;
    std::string roll_;
    std::string address_;
    std::string phone_;
    std::string email_;
    std::string course_;
    std::string semester_;
    std::string year_;
};
//

