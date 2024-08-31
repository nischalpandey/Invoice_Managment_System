#include <iostream>
#include <string>
#include <vector>
#include "db/dbmanager.cpp"

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

void generateInvoice(const Config& config, Database& db) {
    std::string studentName, studentID;
    std::cout << "Enter student name: ";
    std::cin.ignore();
    std::getline(std::cin, studentName);
    std::cout << "Enter student ID: ";
    std::cin >> studentID;

    Invoice invoice(studentName, studentID);
    invoice.addItem(Item("Tuition Fee", 6000.00, 1));
    invoice.addItem(Item("Library Fee", 1000.00, 1));

    std::string filename = invoice.generateFilename();
    invoice.saveToHtmlFile(config.getOutputPath() + filename);
    db.saveInvoice(invoice);
    system("cls");
    std::string fullpth = "start "+config.getOutputPath() + filename;
    system(fullpth.c_str());
    std::cout << "Invoice generated: " << filename << std::endl;
}



void bulkGenerateInvoices(const Config& config, Database& db, int count) {
    for (int i = 0; i < count; ++i) {
        std::string studentName = "Student " + std::to_string(i + 1);
        std::string studentID = "S" + std::to_string(10000 + i);

        Invoice invoice(studentName, studentID);
        invoice.addItem(Item("Tuition Fee", 5000.00, 1));
        invoice.addItem(Item("Library Fee", 200.00, 1));

        std::string filename = invoice.generateFilename();
        invoice.saveToHtmlFile(config.getOutputPath() + filename);
        db.saveInvoice(invoice);
        std::cout << "Generated invoice " << (i + 1) << " of " << count << ": " << filename << std::endl;
    }
}

void searchInvoice(const Config& config, Database& db) {
    std::string invoiceNumber;
    std::cout << "Enter invoice number: ";
    std::cin >> invoiceNumber;

    Invoice invoice = db.getInvoice(invoiceNumber);
    if (invoice.getInvoiceNumber().empty()) {
        std::cout << "Invoice not found.\n";
    } else {
        std::string filename = invoice.generateFilename();
        invoice.saveToHtmlFile(config.getOutputPath() + filename);
        std::cout << "Invoice retrieved: " << filename << std::endl;
    }
}
using namespace std;
int main() {
    try {
        Config config("db/invoices.txt","./outputHTML/");
        Config config0("db/collegeinfo.txt");
        // college
        Database db0(config0.getDatabasePath());
        if (!db0.checkCollegeinfo()) {
            
            
            }


        Database db(config.getDatabasePath());
          cout << R"( 
     ____  _ _ _ __  __           _            
    |  _ \(_) | |  \/  |         | |           
    | |_) |_| | | \  / | __ _ ___| |_ ___ _ __ 
    |  _ <| | | | |\/| |/ _` / __| __/ _ \ '__|
    | |_) | | | | |  | | (_| \__ \ ||  __/ |   
    |____/|_|_|_|_|  |_|\__,_|___/\__\___|_|   
    )" << endl;

        

        while (true) {
            std::cout << "\n1. Generate New Invoice\n"
                      << "2. Search Invoice by Number\n"
                      << "3. Bulk Generate Invoices\n"
                      << "4. About BillMaster\n"
                      << "5. Exit\n"
                      << "Enter your choice: ";
            
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                system("cls");
                    generateInvoice(config, db);
                    break;
                case 2:
                system("cls");
                    searchInvoice(config, db);
                    break;
                case 3: {system("cls");
                    int count;
                    std::cout << "Enter number of invoices to generate: ";
                    std::cin >> count;
                    bulkGenerateInvoices(config, db, count);
                    break;
                }
                case 4:
                    break;
                case 5:
                    return 0;
                default:
                system("cls");
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}