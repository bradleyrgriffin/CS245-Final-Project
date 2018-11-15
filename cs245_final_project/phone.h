#ifndef PHONE_H
#define PHONE_H

#include <string>

class Phone
{
public:
    Phone();

    Phone(const std::string& pNumber, const int& pId);

    int getPhoneNumberId(){return this->phoneNumberId; }
    std::string getPhoneNumber(){return this->phoneNumber; }

private:
    int phoneNumberId;
    std::string phoneNumber;

};

#endif // PHONE_H
