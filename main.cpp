#include "headers/about.h"
#include "headers/invoice.h"


#include<iostream>
#include<string>
using namespace std;


int main() {
    // aboutPage();
    int fileid =    generateInvoice();
    std::cout << "Invoice generated: " << "invoice" + std::to_string(fileid) + ".html" << std::endl;

    // Open the generated invoice in the default browser
    std::string command = "start invoice" + std::to_string(fileid) + ".html";
    system(command.c_str());
    

    
    return 0;
}
