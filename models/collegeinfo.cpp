#include<iostream>
#include<string>

using namespace std;

class CollegeInfo {
public:
    CollegeInfo(const string& name, const string& address, const string& phone, const string& email, const string& website, const string& pan)
        : name_(name), address_(address), phone_(phone), email_(email), website_(website), pan_(pan) {}

    string getName() const { return name_; }
    string getAddress() const { return address_; }
    string getPhone() const { return phone_; }
    string getEmail() const { return email_; }
    string getWebsite() const { return website_; }
    string getPan() const { return pan_; }

private:
    string name_;
    string address_;
    string phone_;
    string email_;
    string website_;
    string pan_;
};
