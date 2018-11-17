#ifndef PHONE_H
#define PHONE_H

#include <string>

class Phone
{
public:
    Phone();

    Phone(const std::string& pNumber, const int& pId, const int& catId);

    int getPhoneNumberId(){return this->phoneNumberId; }
    std::string getPhoneNumber(){return this->phoneNumber; }
    int getCategoryID(){return this->categoryId;}

private:
    int phoneNumberId;
    std::string phoneNumber;
    int categoryId;


};

#endif // PHONE_H
