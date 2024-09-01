

#include <vector>
#include <string>
#include <stdexcept> 
#include <filesystem> 
#include <iostream> 
#include <iomanip>
#include <ctime>
#include <fstream> // For file I/O operations (e.g., std::ifstream, std::ofstream)
#include <sstream>
using namespace std;

// .....................................................
class Config {
public:
    Config(const std::string& databasePath , std::string outputPath = "./output/") {
        // In a real application, you would read from the config file here
        this->databasePath_ = databasePath;
        this->outputPath_ = outputPath;
    }

    std::string getDatabasePath() const { return databasePath_; }
    std::string getOutputPath() const { return outputPath_; }

private:
    std::string databasePath_;
    std::string outputPath_;
};
// .....................................................





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




class CollegeInfo {
public:
    CollegeInfo(){}
    CollegeInfo(const string& name, const string& address, const string& phone, const string& email, const string& website, const string& pan)
        : name_(name), address_(address), phone_(phone), email_(email), website_(website), pan_(pan) {}

    string getName() const { return name_; }
    string getAddress() const { return address_; }
    string getPhone() const { return phone_; }
    string getEmail() const { return email_; }
    string getWebsite() const { return website_; }
    string getPan() const { return pan_; }
    void beautifulsavedata(){
      // save data
        cout << "Enter the name of the college: ";
        getline(cin, name_);
        cout << "Enter the address of the college: ";
        getline(cin, address_);
        cout << "Enter the phone number of the college: ";
        getline(cin, phone_);
        cout << "Enter the email of the college: ";
        getline(cin, email_);
        cout << "Enter the website of the college: ";
        getline(cin, website_);
        cout << "Enter the PAN of the college: ";
        getline(cin, pan_);
        cout <<"--- Monthly Billing Items ---" << endl;
        while (true) {
            cout << "Enter the name of the item: ";
            string name;
            getline(cin, name);
           

            cout << "Enter the price of the item: ";
            double price;
            cin >> price;

            cout << "Enter the quantity of the item: ";
            int quantity;
            cin >> quantity;

            cin.ignore(); // Ignore the newline character

            items_.push_back(Item(name, price, quantity));

            cout << "Do you want to add another item? (y/n): ";
            string choice;
            getline(cin, choice);

            if (choice != "y" && choice != "Y") {
                break;
            }

        }



    }

private:
    string name_;
    string address_;
    string phone_;
    string email_;
    string website_;
    string pan_;
    std::vector<Item> items_;
};



///.....................................................
class Invoice {
public:
    Invoice(const std::string& studentName, const std::string& studentID)
        : studentName_(studentName), studentID_(studentID) {
        generateInvoiceNumber();
        setCurrentDate();
    }

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

    void saveToHtmlFile(const std::string& filename) const {
        std::filesystem::path dirPath = std::filesystem::path(filename).parent_path();

        // Check if the directory exists
        if (!std::filesystem::exists(dirPath)) {
            // Create the directory if it does not exist
            std::filesystem::create_directories(dirPath);
        }
        std::ofstream file(filename);
        if (!file) {
            throw std::runtime_error("Unable to create HTML file");
        }
        file << R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>College Invoice</title>
     <style>
        body { font-family: Arial, sans-serif; line-height: 1.6; color: #333; background-color: #f4f4f4; }
        .container { max-width: 800px; margin: 20px auto; padding: 20px; background-color: #fff; box-shadow: 0 0 10px rgba(0,0,0,0.1); }
        .header { text-align: center; margin-bottom: 20px; border-bottom: 2px solid #333; padding-bottom: 10px; }
        .logo { max-width: 150px; margin-bottom: 10px; }
        .college-info { margin-bottom: 20px; text-align: center; }
        .invoice-details { display: flex; justify-content: space-between; margin-bottom: 20px; border: 1px solid #ddd; padding: 15px; background-color: #f9f9f9; }
        table { width: 100%; border-collapse: collapse; margin-bottom: 20px; }
        th, td { border: 1px solid #ddd; padding: 12px; text-align: left; }
        th { background-color: #f2f2f2; font-weight: bold; }
        .total { font-weight: bold; text-align: right; font-size: 1.2em; margin-top: 20px; }
        .footer { margin-top: 40px; text-align: center; font-size: 0.9em; color: #777; border-top: 1px solid #ddd; padding-top: 20px; }
        .buttons { text-align: center; margin-top: 20px; }
        .btn { display: inline-block; padding: 10px 20px; margin: 0 10px; background-color: #4CAF50; color: white; text-decoration: none; border-radius: 5px; transition: background-color 0.3s; }
        .btn:hover { background-color: #45a049; }
        @media print {
            .buttons { display: none; }
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <img src="../media/logo.jpg" alt="Berojar Banaune Engineering College Logo" class="logo">
            <h1>Berojgar Banaune Engineering College (KEC)</h1>
        </div>
        <div class="college-info">
            <p>123 Kathmandu, Kalimati<br>
            Phone: +977 (01) 123-4567 | Email: billing@kec.edu.np<br>
            Website: www.kec.edu.np | PAN:<strong> ABCDE1234F</strong></p>
        </div>
        <h2 style="text-align: center;">Monthly Invoice</h2>
        <div class="invoice-details">
            <div>
                <p><strong>Invoice No:</strong> )" << invoiceNumber_ << R"(</p>
                <p><strong>Date:</strong> )" << currentDate_ << R"(</p>
                )"  << R"(
            </div>
            <div>
                <p><strong>Student Name:</strong> )" << studentName_ << R"(</p>
                <p><strong>Student Roll:</strong> )" << studentID_ << R"(</p>
            </div>
        </div>
        <table>
            <tr>
                <th>Description</th>
                <th>Quantity</th>
                <th>Unit Price</th>
                <th>Total</th>
            </tr>
)";

        for (const auto& item : items_) {
            file << "            <tr>\n";
            file << "                <td>" << item.getName() << "</td>\n";
            file << "                <td>" << item.getQuantity() << "</td>\n";
            file << "                <td>Rs" << std::fixed << std::setprecision(2) << item.getPrice() << "</td>\n";
            file << "                <td>Rs" << std::fixed << std::setprecision(2) << item.getTotalPrice() << "</td>\n";
            file << "            </tr>\n";
        }

        file << R"(
        </table>
        <div class="total">
            <p>Total Amount: Rs)" << std::fixed << std::setprecision(2) << getTotalAmount() << R"(</p>
        </div>
        <div class="footer">
            <p>Thank you for your payment. If you have any questions, please contact our accounting department.</p>
        </div>
        <div class="buttons">
            <a href="#" class="btn" onclick="window.print();">Print Invoice / Save As PDF</a>
         
        </div>
    </div>
  
</body>
</html>
)";

        file.close();
    }

    std::string generateFilename() const {
        return "invoice_" + invoiceNumber_ + ".html";
    }

    std::string getInvoiceNumber() const { return invoiceNumber_; }
    std::string getStudentName() const { return studentName_; }
    std::string getStudentID() const { return studentID_; }
    std::string getCurrentDate() const { return currentDate_; }
    const std::vector<Item>& getItems() const { return items_; }

    void setInvoiceNumber(const std::string& invoiceNumber) { invoiceNumber_ = invoiceNumber; }
    void setCurrentDate(const std::string& date) { currentDate_ = date; }

private:
    std::string studentName_;
    std::string studentID_;
    std::vector<Item> items_;
    std::string invoiceNumber_;
    std::string currentDate_;

    void generateInvoiceNumber() {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", localTime);
        invoiceNumber_ = "INV-" + std::string(buffer);
    }

    void setCurrentDate() {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        char buffer[11];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
        currentDate_ = std::string(buffer);
    }
};

///.....................................................



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

