#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "models/item.cpp"

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
        body { font-family: Arial, sans-serif; line-height: 1.6; color: #333; background-color: #f4f4f4; height: 100vh;overflow: hidden; }
        .container { max-width: 800px; margin: 20px auto; padding: 20px; background-color: #fff; box-shadow: 0 0 10px rgba(0,0,0,0.1);overflow: auto; box-sizing: border-box; }
        .header { text-align: center; margin-bottom: 20px; border-bottom: 2px solid #333; padding-bottom: 10px; }
        .logo { max-width: 150px; margin-bottom: 10px; }
        .college-info { margin-bottom: 20px; text-align: center; }
        .invoice-details { display: flex; justify-content: space-between; margin-bottom: 20px; border: 1px solid #ddd; padding: 15px; background-color: #f9f9f9;            flex-wrap: wrap;  }
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
            <img src="../media/logo.jpg" alt="Kamnalagne Engineering College Logo" class="logo">
            <h1>Kamnalagne Engineering College (KEC)</h1>
        </div>
        <div class="college-info">
            <p>123 Kathmandu, Kalimati<br>
            Phone: +977 (01) 123-4567 | Email: billing@kec.edu.np<br>
            Website: www.kec.edu.np | PAN: ABCDE1234F</p>
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
                <p><strong>Student ID:</strong> )" << studentID_ << R"(</p>
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
            <p>Thank you for your prompt payment. If you have any questions, please contact our accounting department.</p>
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