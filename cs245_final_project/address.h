#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address
{
public:
    Address();

    Address(const std::string& c, const std::string& s, const std::string& a, const std::string& z, const int& aId, const int& catId);

    std::string getCity(){return this->city;}
    std::string getState(){return this->state; }
    std::string getAddress(){return this->address; }
    std::string getZipcode(){return this->zipcode; }

    int getCategoryId(){return this->categoryId; }
    int getAddressId(){return this->addressId; }

    std::string city;
    std::string state;
    std::string address;
    std::string zipcode;
    int addressId;
    int categoryId;

    std::string displayName;
};

#endif // ADDRESS_H
