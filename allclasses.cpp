

#include <vector>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream> // For file I/O operations (e.g., std::ifstream, std::ofstream)
#include <sstream>
#include <chrono> // For time-based functions
#include <thread> // For sleep_for() function

// For Windows color support
#ifdef _WIN32        // Check if running on Windows, ifdef is a preprocessor directive
#include <windows.h> // For Windows API functions eg. SetConsoleTextAttribute()
#endif               // close ifdef

using namespace std;

// .....................................................
class Config
{
public:
    Config(const std::string &databasePath, std::string outputPath = "./output/")
    {
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

class Utis
{
public:
    void setColor(int color)
    {
#ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
    }
    void colorfulLine()
    {
        string c = "-";  // Character to print
        int length = 60; // Length of the line

        for (int i = 0; i < length; i++)
        {
            setColor(i % 6 + 9); // Cycle through colors
            cout << c;
            this_thread::sleep_for(chrono::milliseconds(15)); // Slight delay for animation effect
        }
        cout << endl;
        setColor(7); // Reset to default color
    }
    void colorfulnoanimation()
    {
        string c = "-";  // Character to print
        int length = 60; // Length of the line

        for (int i = 0; i < length; i++)
        {
            setColor(i % 6 + 9); // Cycle through colors
            cout << c;
        }
        cout << endl;
        setColor(7); // Reset to default color
    }
};

class Item
{
public:
    Item(const std::string &name, double price, int quantity)
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
class Student
{
    // name, roll, address, phone, email, course, semester, year

public:
    Student(const std::string &name, const std::string &roll, const std::string &address, const std::string &phone, const std::string &email, const std::string &course, const std::string &semester, const std::string &year)
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

class CollegeInfo
{
public:
    string name_;
    string address_;
    string phone_;
    string email_;
    string website_;
    string pan_;
    std::vector<Item> items_;
    CollegeInfo() {}
    CollegeInfo(const string &name, const string &address, const string &phone, const string &email, const string &website, const string &pan)
        : name_(name), address_(address), phone_(phone), email_(email), website_(website), pan_(pan) {}

    string getName() const { return name_; }
    string getAddress() const { return address_; }
    string getPhone() const { return phone_; }
    string getEmail() const { return email_; }
    string getWebsite() const { return website_; }
    string getPan() const { return pan_; }
    //
    std::vector<Item> getItems() const { return items_; }
    void beautifulsavedata()
    {
        // Gather college information
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

        // Gather billing items
        cout << "\n--- Monthly Billing Items ---\n";
        while (true)
        {
            string itemName;
            double itemPrice;
            int itemQuantity;

            // Get item details from the user
            cout << "Enter the name of the item: ";
            getline(cin, itemName);

            cout << "Enter the price of the item: ";
            cin >> itemPrice;

            cout << "Enter the quantity of the item: ";
            cin >> itemQuantity;

            // Ignore remaining newline character from the stream
            cin.ignore();

            // Add the item to the list
            items_.emplace_back(itemName, itemPrice, itemQuantity);

            // Ask if the user wants to add another item
            cout << "Do you want to add another item? (y/n): ";
            string choice;
            getline(cin, choice);

            if (choice != "y" && choice != "Y")
            {
                break; // Exit the loop if the user doesn't want to add more items
            }
        }
    }
    void UpdateCollegeInfo(const string &dbpath)
    {
        std::ofstream file(dbpath, std::ios::binary|std::ios::out|std::ios::in|std::ios::app);
        std::ifstream exitingfile (dbpath, std::ios::binary|std::ios::out|std::ios::in|std::ios::app);
        if (!file.is_open())
        {
            throw std::runtime_error("Unable to open or create database file for writing");
        }
        cout << "Press '0' to go back to main menu" << endl;
      
        
        // set the all variables to its value from file
        string line;
        while (std::getline(exitingfile, line))
        {
            std::istringstream iss(line);
            std::string currentInvoiceNumber;
            std::getline(iss, currentInvoiceNumber, '|');
            if (currentInvoiceNumber == "END")
            {
                break;
            }
            std::string name, address, phone, email, website, pan;
            std::getline(iss, name, '|');
            std::getline(iss, address, '|');
            std::getline(iss, phone, '|');
            std::getline(iss, email, '|');
            std::getline(iss, website, '|');
            std::getline(iss, pan, '|');
            name_ = name;
            address_ = address;
            phone_ = phone;
            email_ = email;
            website_ = website;
            pan_ = pan;
            while (std::getline(exitingfile, line) && line != "END")
            {
                std::istringstream itemIss(line);
                std::string itemType;
                std::getline(itemIss, itemType, '|');
                if (itemType == "ITEM")
                {
                    std::string itemName;
                    double price;
                    int quantity;
                    std::getline(itemIss, itemName, '|');
                    itemIss >> price;
                    itemIss.ignore();
                    itemIss >> quantity;
                    items_.emplace_back(itemName, price, quantity);
                }
            }
        }





        cout << "Current College Information" << endl;
        cout << "1." << "Name: " << name_ << endl;
        cout << "2." << "Address: " << address_ << endl;
        cout << "3." << "Phone: " << phone_ << endl;
        cout << "4." << "Email: " << email_ << endl;
        cout << "5." << "Website: " << website_ << endl;
        cout << "6." << "PAN: " << pan_ << endl;

        cout << "7." << "Items: " << endl;
        for (const auto &item : items_)
        {
            cout << "Name: " << item.getName() << ", Price: " << item.getPrice() << ", Quantity: " << item.getQuantity() << endl;
        }
        cout << "Enter the number of the field you want to update: ";
        
      
        
        int choice;
        cin >> choice;
        if (choice == 0)
        {
            return;
        }
        
        cin.ignore();
        switch (choice)
        {
        case 1:
            cout << "Enter the new name of the college: ";
            getline(cin, name_);
            break;
        case 2:
            cout << "Enter the new address of the college: ";
            getline(cin, address_);
            break;
        case 3:

            cout << "Enter the new phone number of the college: ";
            getline(cin, phone_);
            break;
        case 4:

            cout << "Enter the new email of the college: ";
            getline(cin, email_);
            break;
        case 5:

            cout << "Enter the new website of the college: ";
            getline(cin, website_);
            break;
        case 6:

            cout << "Enter the new PAN of the college: ";
            getline(cin, pan_);
            break;
        case 7:
            cout << "Enter the new items: " << endl;
            items_.clear();
            while (true)
            {
                string itemName;
                double itemPrice;
                int itemQuantity;

                // Get item details from the user
                cout << "Enter the name of the item: ";
                getline(cin, itemName);

                cout << "Enter the price of the item: ";
                cin >> itemPrice;

                cout << "Enter the quantity of the item: ";
                cin >> itemQuantity;

                // Ignore remaining newline character from the stream
                cin.ignore();

                // Add the item to the list
                items_.emplace_back(itemName, itemPrice, itemQuantity);
               
                // Ask if the user wants to add another item
                cout << "Do you want to add another item? (y/n): ";
                string choice;
                getline(cin, choice);

                if (choice != "y" && choice != "Y")
                {
                    break; // Exit the loop if the user doesn't want to add more items
                }
            }
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            break;
        }
        file << name_ << "|"
             << address_ << "|"
             << phone_ << "|"
             << email_ << "|"
             << website_ << "|"
             << pan_ << "\n";
        for (const auto &item : items_)
        {

            file << "ITEM|" << item.getName() << "|" << item.getPrice() << "|" << item.getQuantity() << "\n";
        }
        file << "END\n";
        file.close();
        exitingfile.close();
    }



};

///.....................................................
class Invoice
{
public:
    Invoice(const std::string &studentName, const std::string &studentID)
        : studentName_(studentName), studentID_(studentID)
    {
        generateInvoiceNumber();
        setCurrentDate();
    }

   

    double getTotalAmount() const
    {
        double total = 0;
        for (const auto &item : collegeinfo_.getItems())
        {
            total += item.getTotalPrice();
        }
        return total;
    }

    void saveToHtmlFile(const std::string &filename) const
    {
        std::filesystem::path dirPath = std::filesystem::path(filename).parent_path();

        // Check if the directory exists
        if (!std::filesystem::exists(dirPath))
        {
            // Create the directory if it does not exist
            std::filesystem::create_directories(dirPath);
        }

        std::ofstream file(filename);
        if (!file)
        {
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
            <h2>)" << collegeinfo_.getName() << R"(</h2>
        </div>
        <div class="college-info">
            <p>123 Kathmandu, Kalimati<br>
            Phone: +977 (01) 123-4567 | Email: billing@kec.edu.np<br>
            Website: www.kec.edu.np | PAN:<strong> ABCDE1234F</strong></p>
        </div>
        <h2 style="text-align: center;">Invoice</h2>
        <div class="invoice-details">
            <div>
                <p><strong>Invoice No:</strong> )" << invoiceNumber_ << R"(</p>
                <p><strong>Date:</strong> )" << currentDate_ << R"(</p>
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
            </tr>)";

        for (const auto &item : collegeinfo_.getItems())
        {
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
</html>)";

        file.close();
    }

    std::string generateFilename() const
    {
        return invoiceNumber_ + ".html";
    }

    std::string getInvoiceNumber() const { return invoiceNumber_; }
    std::string getStudentName() const { return studentName_; }
    std::string getStudentID() const { return studentID_; }
    std::string getCurrentDate() const { return currentDate_; }
    CollegeInfo getCollegeInfo() const { return collegeinfo_; }

    void setCollegeInfo(const std::string &dbPath)
    {
        // Read from file and set the value to collegeinfo_
        std::ifstream infile(dbPath, std::ios::binary | std::ios::in);
        
        if (!infile.is_open())
        {
            throw std::runtime_error("Unable to open database file for reading");
        }
        std::string line;
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            std::string name, address, phone, email, website, pan;
            std::getline(iss, name, '|');
            std::getline(iss, address, '|');
            std::getline(iss, phone, '|');
            std::getline(iss, email, '|');
            std::getline(iss, website, '|');
            std::getline(iss, pan, '|');
            collegeinfo_ = CollegeInfo(name, address, phone, email, website, pan);
            while (std::getline(infile, line) && line != "END")
            {
                std::istringstream itemIss(line);
                std::string itemType;
                std::getline(itemIss, itemType, '|');
                if (itemType == "ITEM")
                {
                    std::string itemName;
                    double price;
                    int quantity;
                    std::getline(itemIss, itemName, '|');
                    itemIss >> price;
                    itemIss.ignore();
                    itemIss >> quantity;
                    collegeinfo_.getItems().emplace_back(itemName, price, quantity);
                }
            }
        }
    // checking items
   if (collegeinfo_.getItems().empty()){
   collegeinfo_.items_ = {Item("Tuition Fee", 6000, 1), Item("Library Fee", 1000, 1)};
   }

        infile.close();

    }

    void setInvoiceNumber(const std::string &invoiceNumber) { invoiceNumber_ = invoiceNumber; }
    void setCurrentDate(const std::string &date) { currentDate_ = date; }

private:
    std::string studentName_;
    std::string studentID_;
    CollegeInfo collegeinfo_;
    std::string invoiceNumber_;
    std::string currentDate_;

    void generateInvoiceNumber()
    {
        std::time_t now = std::time(nullptr);
        std::tm *localTime = std::localtime(&now);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", localTime);
        invoiceNumber_ = std::string(buffer);
    }

    void setCurrentDate()
    {
        std::time_t now = std::time(nullptr);
        std::tm *localTime = std::localtime(&now);
        char buffer[11];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
        currentDate_ = std::string(buffer);
    }
};
///.....................................................

class Database
{
public:
    Database(const std::string &dbPath) : dbPath_(dbPath)
    {
        // Extract the directory path from the dbPath
        std::filesystem::path dirPath = std::filesystem::path(dbPath_).parent_path();

        // Check if the directory exists
        if (!std::filesystem::exists(dirPath))
        {
            // Create the directory if it does not exist
            std::filesystem::create_directories(dirPath);
        }
    }

    bool checkCollegeinfo()
    {
        std::ifstream file(dbPath_, std::ios::out | std::ios::binary);
        if (!file)
        {
            return false;
        }
        return true;
    }

    void saveCollegeinfo(const CollegeInfo &collegeinfo)
    {
        std::ofstream file(dbPath_, std::ios::app | std::ios::binary | std::ios::in|std::ios::out); //  
        if (!file.is_open())
        {
            throw std::runtime_error("Unable to open or create database file for writing");
        }
        file << collegeinfo.getName() << "|"
             << collegeinfo.getAddress() << "|"
             << collegeinfo.getPhone() << "|"
             << collegeinfo.getEmail() << "|"
             << collegeinfo.getWebsite() << "|"
             << collegeinfo.getPan() << "\n";

        for (const auto &item : collegeinfo.getItems())
        {
            file << "ITEM|" << item.getName() << "|" << item.getPrice() << "|" << item.getQuantity() << "\n";
        }

        file << "END\n";

    }

    void saveInvoice(Invoice &invoice)
    {

        // print dbpath
        std::cout << dbPath_ << std::endl;

        // All modes are supported ,so error handling is not required
        // Try to open the file in append mode; if it doesn't exist, create it
        std::ofstream file(dbPath_, std::ios::app | std::ios::binary);

        // Check if the file was successfully opened
        if (!file.is_open())
        {
            throw std::runtime_error("Unable to open or create database file for writing");
        }
        file << invoice.getInvoiceNumber() << "|"
             << invoice.getStudentName() << "|"
             << invoice.getStudentID() << "|"
             << invoice.getCurrentDate() << "|"
             << invoice.getTotalAmount() << "\n";

        for (const auto &item : invoice.getCollegeInfo().getItems())
        {
            file << "ITEM|" << item.getName() << "|" << item.getPrice() << "|" << item.getQuantity() << "\n";
        }

        file << "END\n";
    }

    Invoice getInvoice(const std::string &invoiceNumber)
    {
        std::ifstream file(dbPath_, std::ios::out | std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Unable to open database file for reading");
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string currentInvoiceNumber;
            std::getline(iss, currentInvoiceNumber, '|');

            if (currentInvoiceNumber == invoiceNumber)
            {
                std::string studentName, studentID, date;
                double totalAmount;
                std::getline(iss, studentName, '|');
                std::getline(iss, studentID, '|');
                std::getline(iss, date, '|');
                iss >> totalAmount;

                Invoice invoice(studentName, studentID);
                invoice.setInvoiceNumber(invoiceNumber);
                invoice.setCurrentDate(date);

                while (std::getline(file, line) && line != "END")
                {
                    std::istringstream itemIss(line);
                    std::string itemType;
                    std::getline(itemIss, itemType, '|');
                    if (itemType == "ITEM")
                    {
                        std::string itemName;
                        double price;
                        int quantity;
                        std::getline(itemIss, itemName, '|');
                        itemIss >> price;
                        itemIss.ignore();
                        itemIss >> quantity;
                      invoice.getCollegeInfo().getItems().emplace_back(itemName, price, quantity);
                    }
                }

                return invoice;
            }

            // Skip to the end of the current invoice
            while (std::getline(file, line) && line != "END")
            {
            }
        }

        return Invoice("", ""); // Return empty invoice if not found
    }

    std::vector<std::string> getAllInvoiceNumbers()
    {
        std::vector<std::string> invoiceNumbers;
        std::ifstream file(dbPath_, std::ios::app | std::ios::out | std::ios::in | std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Unable to open database file for reading");
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string invoiceNumber;
            std::getline(iss, invoiceNumber, '|');
            invoiceNumbers.push_back(invoiceNumber);

            // Skip to the end of the current invoice
            while (std::getline(file, line) && line != "END")
            {
            }
        }

        return invoiceNumbers;
    }

private:
    std::string dbPath_;
};
