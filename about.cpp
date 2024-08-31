#include <iostream> // For standard I/O operations
#include <string> // For string operations

#include <iomanip> // For setw() function
#include <chrono> // For time-based functions
#include <thread>  // For sleep_for() function

// For Windows color support
#ifdef _WIN32  // Check if running on Windows, ifdef is a preprocessor directive
#include <windows.h>  // For Windows API functions eg. SetConsoleTextAttribute()
#endif // close ifdef

using namespace std; // This we all know..

// Function to set console text color (Windows only)
void setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
}

// Function to create a colorful line
void colorfulLine(char c = '-', int length = 60) {
    for (int i = 0; i < length; i++) {
        setColor(i % 6 + 9); // Cycle through colors
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(5)); // Slight delay for animation effect
    }
    cout << endl;
    setColor(7); // Reset to default color
}

void showaboutPage() {
    // Clear screen
    #ifdef _WIN32
    system("cls"); // system() used to run cmd commands
    #else
    system("clear");
    #endif

    colorfulLine('='); // your coloring function

    // ASCII Art Logo // You can create our own ASCII art use: https://patorjk.com/software/taag/#p=display&f=Big&t=Nischal
    setColor(14); // Yellow
    // R"()" is a raw string literal, it allows us to write multi-line strings without escaping special characters
    cout << R"( 
     ____  _ _ _ __  __           _            
    |  _ \(_) | |  \/  |         | |           
    | |_) |_| | | \  / | __ _ ___| |_ ___ _ __ 
    |  _ <| | | | |\/| |/ _` / __| __/ _ \ '__|
    | |_) | | | | |  | | (_| \__ \ ||  __/ |   
    |____/|_|_|_|_|  |_|\__,_|___/\__\___|_|   
    )" << endl;
    setColor(7); // Reset color

    colorfulLine('+');

    // Application details
    setColor(11); // Light Cyan
    cout << setw(30) << right << "App Name: " << setw(30) << left << "BillMaster" << endl;
    cout << setw(30) << right << "Version: " << setw(30) << left << "1.0" << endl;
    cout << setw(30) << right << "Built with: " << setw(30) << left << "C++ & OOP Concepts" << endl;
    cout << setw(30) << right << "Date: " << setw(30) << left << "01/09/2024" << endl;
    cout << setw(30) << right << "License: " << setw(30) << left << "MIT License" << endl;
    cout << setw(30) << right << "GitHub: " << setw(30) << left << "nischalpandey/invoice-management-system" << endl;
    // cout<<setw(30)<<right<<"Author: "<<setw(30)<<left<<"Nischal Pandey"<<endl;
    colorfulLine('-');

    // Team information
    setColor(10); // Light Green
    cout << "Team Members:" << endl;
    
    cout << " -Ankit Sharma" << endl;
    cout << " -Prajwol Dukhuwa" << endl;
    cout << " -Pawan Kumar Sha" << endl;
    cout << " -Nischal Pandey" << endl;

    colorfulLine('+');

    setColor(15); // Bright White
    cout << "Press Enter to continue...";
    cin.get(); // cin.get() can get any input from the user 

 
}